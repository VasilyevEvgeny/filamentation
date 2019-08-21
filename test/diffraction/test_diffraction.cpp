//
// Created by vasilyev on 17.07.2019.
//

#include <vector>
#include <omp.h>
#include <map>

#include "gtest/gtest.h"
#include "logger/logger.h"
#include "pulsed_beam/base_pulsed_beam.h"
#include "manager/config_manager/config_manager.h"
#include "propagator/propagator.h"
#include "postprocessor_diffraction/postprocessor_diffraction.h"



int main(int argc, char** argv) {

    /*
     * config manager
     */

    std::string path_to_config = "test/diffraction/config.yml";
    ConfigManager config_manager(path_to_config);
    config_manager.parse_and_validate_config();

    DirManager dir_manager;

    std::string multidir_name = config_manager.prefix + "_" + dir_manager.get_current_datetime();
    std::vector<std::pair<size_t, size_t>> ms = {std::make_pair(0, 0),
                                                 std::make_pair(1, 1)};

    std::shared_ptr<BasePulsedBeam> pulsed_beam;
    std::shared_ptr<Propagator> propagator;
    for (auto& item : ms) {

        config_manager.M = item.first;
        config_manager.m = item.second;

        std::string current_results_dir_name = "M=" + std::to_string(config_manager.M) + "_m=" + std::to_string(config_manager.m);

        /*
        * dir manager
        */

        dir_manager = DirManager(config_manager, multidir_name, current_results_dir_name);

        /*
         * logger
         */

        auto logger = std::make_shared<Logger>(config_manager, dir_manager, true);

        /*
         * postprocessor
         */

        std::shared_ptr<Postprocessor> postprocessor = std::make_shared<PostprocessorDiffraction>(config_manager,
                                                                                                  dir_manager,
                                                                                                  logger);

        /*
         * medium
         */

        std::shared_ptr<BaseMedium> medium;
        if (config_manager.medium == "SiO2") {
            medium = std::make_shared<SiO2>(config_manager, logger);
        } else if (config_manager.medium == "CaF2") {
            medium = std::make_shared<CaF2>(config_manager, logger);
        } else {
            medium = std::make_shared<LiF>(config_manager, logger);
        }


        /*
         * pulsed_beam
         */

        if (config_manager.M == 0 && config_manager.m == 0) {
            pulsed_beam = std::make_shared<Gauss>(medium,
                                                  config_manager,
                                                  logger);
        } else if (config_manager.m == 0) {
            pulsed_beam = std::make_shared<Ring>(medium,
                                                 config_manager,
                                                 logger);
        } else {
            pulsed_beam = std::make_shared<Vortex>(medium,
                                                   config_manager,
                                                   logger);
        }

        config_manager.dz_0 = pulsed_beam->z_diff / config_manager.n_z;

        /*
         * propagator
         */

        propagator = std::make_shared<Propagator>(pulsed_beam,
                                                  config_manager,
                                                  dir_manager,
                                                  postprocessor,
                                                  logger
        );

        propagator->propagate();

    }


    return 0;
}

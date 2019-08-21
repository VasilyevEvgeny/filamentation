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
#include "misc/misc.h"


int main(int argc, char** argv) {

    // config_manager
    ConfigManager config_manager(std::string("test/diffraction/test_diffraction_config.yml"));

    // multidir_name
    std::string multidir_name = config_manager.prefix + "_" + get_current_datetime("dir_manager");

    // parameters
    std::vector<std::pair<size_t, size_t>> ms = {std::make_pair(0, 0),
                                                 std::make_pair(1, 1)};

    // main cycle
    for (auto& item : ms) {

        // current_results_dir_name
        config_manager.M = item.first;
        config_manager.m = item.second;
        std::string current_results_dir_name = "M=" + std::to_string(config_manager.M) + "_m=" + std::to_string(config_manager.m);

        // postprocessor
        std::shared_ptr<Postprocessor> postprocessor = std::make_shared<PostprocessorDiffraction>(config_manager);

        // propagator
        auto propagator = std::make_shared<Propagator>(config_manager,
                                                       postprocessor,
                                                       multidir_name,
                                                       current_results_dir_name);
        // corrections for test_diffraction
        propagator->dz = propagator->pulsed_beam->z_diff / propagator->n_z;

        // propagate!
        propagator->propagate();
    }


    return 0;
}

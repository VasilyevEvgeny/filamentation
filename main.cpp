#include <iostream>
#include <fstream>
#include <sstream>
#include <omp.h>
#include <map>
#include <string>
#include <memory>

#include "logger/logger.h"
#include "pulsed_beam/base_pulsed_beam.h"
#include "manager/config_manager/config_manager.h"
#include "propagator/propagator.h"


int main(int argc, char** argv) {

    /*
     * config manager
     */

    std::string path_to_config = "config.yml";
    ConfigManager config_manager(path_to_config);
    config_manager.parse_and_validate_config();

    /*
     * dir manager
     */

    DirManager dir_manager(config_manager);


    /*
     * logger
     */

    bool verbose = true;
    auto logger = std::make_shared<Logger>(config_manager, dir_manager, verbose);

    /*
     * postprocessor
     */

    auto postprocessor = std::make_shared<Postprocessor>(config_manager,
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

    std::shared_ptr<BasePulsedBeam> pulsed_beam;

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


    /*
     * propagator
     */

    auto propagator = std::make_shared<Propagator>(pulsed_beam,
                                                   config_manager,
                                                   dir_manager,
                                                   postprocessor,
                                                   logger);

    propagator->propagate();


    return 0;
}

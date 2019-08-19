#include <iostream>
#include <fstream>
#include <sstream>
#include <omp.h>
#include <map>
#include <string>
#include <omp.h>
#include <memory>

#include "pulsed_beam/base_pulsed_beam.h"
#include "manager/config_manager/config_manager.h"
#include "propagator/propagator.h"


int main(int argc, char** argv) {

    /*
     * config
     */

    std::string path_to_config = "config.yml";
    ConfigManager config_manager = ConfigManager(path_to_config);
    config_manager.parse_and_validate_config();


    /*
     * threads
     */

    omp_set_num_threads(config_manager.num_threads);


    /*
     * medium
     */

    std::shared_ptr<BaseMedium> medium;

    if (config_manager.medium == "SiO2") {
        medium = std::make_shared<SiO2>(config_manager.lambda_0);
    } else if (config_manager.medium == "CaF2") {
        medium = std::make_shared<CaF2>(config_manager.lambda_0);
    } else {
        medium = std::make_shared<LiF>(config_manager.lambda_0);
    }

    /*
     * pulsed_beam
     */

    std::shared_ptr<BasePulsedBeam<BaseMedium>> pulsed_beam;

    if (config_manager.M == 0 && config_manager.m == 0) {
        pulsed_beam = std::make_shared<Gauss<BaseMedium>>(medium,
                                                          config_manager.lambda_0,
                                                          config_manager.r_0,
                                                          config_manager.n_r,
                                                          config_manager.t_0,
                                                          config_manager.n_t,
                                                          config_manager.p_0_to_p_cr);
    } else if (config_manager.m == 0) {
        pulsed_beam = std::make_shared<Ring<BaseMedium>>(medium,
                                                          config_manager.lambda_0,
                                                          config_manager.M,
                                                          config_manager.r_0,
                                                          config_manager.n_r,
                                                          config_manager.t_0,
                                                          config_manager.n_t,
                                                          config_manager.p_0_to_p_cr);
    } else {
        pulsed_beam = std::make_shared<Vortex<BaseMedium>>(medium,
                                                           config_manager.lambda_0,
                                                           config_manager.M,
                                                           config_manager.m,
                                                           config_manager.r_0,
                                                           config_manager.n_r,
                                                           config_manager.t_0,
                                                           config_manager.n_t,
                                                           config_manager.p_0_to_p_cr);
    }

    /*
     * propagator
     */

    Propagator<BasePulsedBeam<BaseMedium>> propagator(
            config_manager,
            pulsed_beam);

    propagator.propagate();


    return 0;
}

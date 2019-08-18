#include <iostream>
#include <fstream>
#include <sstream>
#include <omp.h>
#include <map>
#include <string>
#include <omp.h>

#include "pulsed_beam/base_pulsed_beam/base_pulsed_beam.h"
#include "manager/config_manager.h"
#include "propagator.h"



int main(int argc, char** argv) {

    // config
    std::string path_to_config = "config.yml";
    ConfigManager config_manager = ConfigManager(path_to_config);
    config_manager.parse_and_validate_config();

    // threads
    omp_set_num_threads(config_manager.num_threads);

    // medium
    if (config_manager.medium == "SiO2") {
#ifndef MEDIUM
#define MEDIUM SiO2
#endif
    }
    else if (config_manager.medium == "CaF2") {
#ifndef MEDIUM
#define MEDIUM CaF2
#endif
    }
    else if (config_manager.medium == "LiF") {
#ifndef MEDIUM
#define MEDIUM LiF
#endif
    }

    MEDIUM medium(config_manager.lambda_0);

    std::cout << "MEDIUM in main: " << &(medium) << std::endl;

    // pulsed_beam

    if (config_manager.M == 0 && config_manager.m == 0) {
#ifndef PULSED_BEAM
#define PULSED_BEAM Gauss
#endif

        Gauss<MEDIUM> pulsed_beam(
            medium,
            config_manager.lambda_0,
            config_manager.r_0,
            config_manager.n_r,
            config_manager.t_0,
            config_manager.n_t,
            config_manager.p_0_to_p_cr);

        std::cout << "PB in main: " << &(pulsed_beam) << std::endl;

        // propagator
        Propagator<Gauss<MEDIUM>> propagator(
                config_manager,
                pulsed_beam);

        propagator.propagate();

    }
    else if (config_manager.m == 0) {
#ifndef PULSED_BEAM
#define PULSED_BEAM Ring
#endif

        Ring<MEDIUM> pulsed_beam(
            medium,
            config_manager.lambda_0,
            config_manager.M,
            config_manager.r_0,
            config_manager.n_r,
            config_manager.t_0,
            config_manager.n_t,
            config_manager.p_0_to_p_cr);

        // propagator
        Propagator<Ring<MEDIUM>> propagator(
                config_manager,
                pulsed_beam);

        //propagator.propagate();

    }
    else {
#ifndef PULSED_BEAM
#define PULSED_BEAM Vortex
#endif

        Vortex<MEDIUM> pulsed_beam(
                medium,
                config_manager.lambda_0,
                config_manager.M,
                config_manager.m,
                config_manager.r_0,
                config_manager.n_r,
                config_manager.t_0,
                config_manager.n_t,
                config_manager.p_0_to_p_cr);

        // propagator
        Propagator<Vortex<MEDIUM>> propagator(
                config_manager,
                pulsed_beam);

        propagator.propagate();

    }


    return 0;
}
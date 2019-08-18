//
// Created by vasilyev on 28.06.2019.
//



#include "propagator.h"

#include <vector>


template<template<typename, typename...> class PulsedBeam, typename Medium>
Propagator<PulsedBeam<Medium>>::Propagator() = default;


template<template<typename, typename...> class PulsedBeam, typename Medium>
Propagator<PulsedBeam<Medium>>::Propagator(
        ConfigManager& _config_manager,
        std::shared_ptr<PulsedBeam<Medium>> _pulsed_beam)
: config_manager(_config_manager)
, pulsed_beam(_pulsed_beam) {

    std::cout << pulsed_beam->info << std::endl;

    dir_manager = DirManager(config_manager);
    processor = Processor(config_manager,
                          dir_manager);

    // ionization_table
    pulsed_beam->medium->ionization.initialize_ionization_table(config_manager,
                                                                pulsed_beam->lambda_0);

    std::cout << "LINEAR TERMS:" << std::endl;
    for (auto& term : config_manager.active_linear_terms) {
        std::cout << term << std::endl;
    }

    std::cout << "NONLINEAR TERMS:" << std::endl;
    for (auto& term : config_manager.active_nonlinear_terms) {
        std::cout << term << std::endl;
    }

    // executors
    linear_executor = std::make_shared<LinearExecutor<PulsedBeam<Medium>>>(config_manager, pulsed_beam);
    nonlinear_executor = std::make_shared<NonlinearExecutor<PulsedBeam<Medium>>>(config_manager, pulsed_beam);

    logger = Logger<PulsedBeam<Medium>, Processor>(config_manager, dir_manager, processor, pulsed_beam,
                                                   linear_executor, nonlinear_executor);

    logger.save_initial_parameters_to_pdf(true, false);
    logger.save_initial_parameters_to_yml();
}

template<template<typename, typename...> class PulsedBeam, typename Medium>
Propagator<PulsedBeam<Medium>>::~Propagator() = default;



template<template<typename, typename...> class PulsedBeam, typename Medium>
void Propagator<PulsedBeam<Medium>>::propagate() {
    /*
     * Main cycle
     */

    auto t1 = std::chrono::high_resolution_clock::now();

    double z = 0.0;
    double dz = config_manager.dz_0;
    for (int step = 0; step < config_manager.n_z + 1; ++step) {
        if (step) {

            /*
             * effects
             */

            linear_executor->execute(dz);
            nonlinear_executor->execute(dz);

            z += dz;
        }

        if (config_manager.save_every) {
            if (!(step % config_manager.save_every)) {
                logger.save_field(step);
                logger.save_plasma(step);
            }
        }

        logger.flush_current_state(step, z, dz);

        if (config_manager.print_current_state_every) {
            if (!(step % config_manager.print_current_state_every)) {
                logger.print_current_state(step, z, dz);
            }
        }
    }

    auto t2 = std::chrono::high_resolution_clock::now();

    std::chrono::duration<float> fsec = t2 - t1;
    std::chrono::hours d = std::chrono::duration_cast<std::chrono::hours>(fsec);

    std::cout << fsec.count() << "s\n";

    logger.save_states_to_csv();
    logger.processor.go();
}


template class Propagator<Gauss<SiO2>>;
template class Propagator<Gauss<CaF2>>;
template class Propagator<Gauss<LiF>>;
template class Propagator<Ring<SiO2>>;
template class Propagator<Ring<CaF2>>;
template class Propagator<Ring<LiF>>;
template class Propagator<Vortex<SiO2>>;
template class Propagator<Vortex<CaF2>>;
template class Propagator<Vortex<LiF>>;

template class Propagator<BasePulsedBeam<BaseMedium>>;

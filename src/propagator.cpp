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
        PulsedBeam<Medium>& _pulsed_beam)
: config_manager(_config_manager)
, pulsed_beam(&_pulsed_beam) {

    dir_manager = DirManager(config_manager);
    processor = Processor(config_manager,
                          dir_manager);

    // ionization_table
    pulsed_beam->medium->ionization.initialize_ionization_table(config_manager,
                                                                pulsed_beam->lambda_0);

    // linear terms
    diffraction = Diffraction<PulsedBeam<Medium>>(pulsed_beam, config_manager.T.at("diffraction"));
    dispersion_full = DispersionFull<PulsedBeam<Medium>>(pulsed_beam, config_manager.T.at("dispersion"));
    dispersion_gvd = DispersionGVD<PulsedBeam<Medium>>(pulsed_beam);

    // nonlinear terms
    kerr = Kerr<PulsedBeam<Medium>>(pulsed_beam, config_manager.kerr_info, config_manager.T.at("kerr"));
    plasma = Plasma<PulsedBeam<Medium>>(pulsed_beam, config_manager.T.at("plasma"));
    bremsstrahlung = Bremsstrahlung<PulsedBeam<Medium>>(pulsed_beam, config_manager.T.at("bremsstrahlung"));
    dissipation = Dissipation<PulsedBeam<Medium>>(pulsed_beam);

    // container for linear terms
    linear_terms_pool.insert(std::pair<std::string, BaseLinearTerm<PulsedBeam<Medium>>*>(diffraction.name, &diffraction));
    linear_terms_pool.insert(std::pair<std::string, BaseLinearTerm<PulsedBeam<Medium>>*>(dispersion_full.name, &dispersion_full));
    linear_terms_pool.insert(std::pair<std::string, BaseLinearTerm<PulsedBeam<Medium>>*>(dispersion_gvd.name, &dispersion_gvd));

    // container for nonlinear terms
    nonlinear_terms_pool.insert(std::pair<std::string, BaseNonlinearTerm<PulsedBeam<Medium>>*>(kerr.name, &kerr));
    nonlinear_terms_pool.insert(std::pair<std::string, BaseNonlinearTerm<PulsedBeam<Medium>>*>(plasma.name, &plasma));
    nonlinear_terms_pool.insert(std::pair<std::string, BaseNonlinearTerm<PulsedBeam<Medium>>*>(bremsstrahlung.name, &bremsstrahlung));
    nonlinear_terms_pool.insert(std::pair<std::string, BaseNonlinearTerm<PulsedBeam<Medium>>*>(dissipation.name, &dissipation));

    // active terms
    active_linear_terms = config_manager.active_linear_terms;
    active_nonlinear_terms = config_manager.active_nonlinear_terms;

    // executors
    linear_executor = LinearExecutor<PulsedBeam<Medium>>(pulsed_beam, active_linear_terms, linear_terms_pool);
    nonlinear_executor = NonlinearExecutor<PulsedBeam<Medium>>(pulsed_beam, active_nonlinear_terms, nonlinear_terms_pool,
            &dissipation);

    logger = Logger<PulsedBeam<Medium>, Processor>(config_manager, dir_manager, processor, pulsed_beam,
                                                   linear_terms_pool, nonlinear_terms_pool,
                                                   active_linear_terms, active_nonlinear_terms,
                                                   nonlinear_executor.kinetic_equation);

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
    for (int step = 0; step < n_z + 1; ++step) {
        if (step) {

            /*
             * effects
             */

            linear_executor.execute(dz);

            nonlinear_executor.execute(dz);

            z += dz;
        }

        if (save_field_every) {
            if (!(step % save_field_every)) {
                logger.save_field(step);
                logger.save_plasma(step);
            }
        }

        logger.flush_current_state(step, z, dz);

        if (print_current_state_every) {
            if (!(step % print_current_state_every)) {
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

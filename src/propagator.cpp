//
// Created by vasilyev on 28.06.2019.
//



#include "propagator.h"

#include <vector>

#define base_term BaseTerm<PulsedBeam<Medium>>


template<template<typename, typename...> class PulsedBeam, typename Medium>
Propagator<PulsedBeam<Medium>>::Propagator() = default;


template<template<typename, typename...> class PulsedBeam, typename Medium>
Propagator<PulsedBeam<Medium>>::Propagator(
        std::map<std::string, std::string>& _args,
        PulsedBeam<Medium>& _pulsed_beam,
        size_t _n_z,
        double _dz,
        size_t _print_current_state_every,
        size_t _save_field_every):
        pulsed_beam(&_pulsed_beam)
        , n_z(_n_z)
        , dz(_dz)
        , print_current_state_every(_print_current_state_every)
        , save_field_every(_save_field_every)
{

    std::cout << "PULSED BEAM ADDRESS IN PROPAGATOR: " << &(*pulsed_beam) << std::endl;

    track_info = {{"n_z", (double)(n_z + 1)},
                  {"dz", dz}};
    manager = Manager(_args);
    processor = Processor(_args, manager);

    // ionization_table
    pulsed_beam->medium->ionization.initialize_ionization_table(_args,
                                                                manager.ionization_tables_dir,
                                                                pulsed_beam->medium->name,
                                                                pulsed_beam->lambda_0);

    // linear terms
    diffraction = Diffraction<PulsedBeam<Medium>>(pulsed_beam);
    dispersion_full = DispersionFull<PulsedBeam<Medium>>(pulsed_beam);
    std::string mode = "sweep";
    dispersion_gvd = DispersionGVD<PulsedBeam<Medium>>(pulsed_beam, mode);

    // nonlinear terms
    kerr_instant = KerrInstant<PulsedBeam<Medium>>(pulsed_beam);

    // constainers for linear terms
    linear_terms_pool.insert(std::pair<std::string, BaseLinearTerm<PulsedBeam<Medium>>*>(diffraction.name, &diffraction));
    linear_terms_pool.insert(std::pair<std::string, BaseLinearTerm<PulsedBeam<Medium>>*>(dispersion_full.name, &dispersion_full));
    linear_terms_pool.insert(std::pair<std::string, BaseLinearTerm<PulsedBeam<Medium>>*>(dispersion_gvd.name, &dispersion_gvd));

    // constainers for nonlinear terms
    nonlinear_terms_pool.insert(std::pair<std::string, BaseNonlinearTerm<PulsedBeam<Medium>>*>(kerr_instant.name, &kerr_instant));

    // active terms
    active_linear_terms = {"diffraction", "dispersion_full"};
    active_nonlinear_terms = {"kerr_instant"};

    // executors
    linear_executor = LinearExecutor<PulsedBeam<Medium>>(pulsed_beam, active_linear_terms, linear_terms_pool);
    nonlinear_executor = NonlinearExecutor<PulsedBeam<Medium>>(pulsed_beam, active_nonlinear_terms, nonlinear_terms_pool);



    logger = Logger<PulsedBeam<Medium>, Processor>(_args, pulsed_beam, manager, processor, track_info,
                                                   linear_terms_pool, nonlinear_terms_pool,
                                                   active_linear_terms, active_nonlinear_terms);

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
            }
        }

        logger.flush_current_state(step, z);

        if (print_current_state_every) {
            if (!(step % print_current_state_every)) {
                logger.print_current_state(step, z);
            }
        }
    }

    auto t2 = std::chrono::high_resolution_clock::now();

    std::chrono::duration<float> fsec = t2 - t1;
    std::chrono::milliseconds d = std::chrono::duration_cast<std::chrono::milliseconds>(fsec);

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

//
// Created by vasilyev on 28.06.2019.
//



#include "propagator.h"


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
    logger = Logger<PulsedBeam<Medium>, Processor>(_args, pulsed_beam, manager, processor, track_info);

    logger.save_initial_parameters_to_pdf(true, true);
    logger.save_initial_parameters_to_yml();


    fourier_executor = FourierExecutor<PulsedBeam<Medium>>(pulsed_beam);
    diffraction_executor = DiffractionExecutor<PulsedBeam<Medium>>(pulsed_beam);
    dispersion_executor_full = DispersionExecutorFull<PulsedBeam<Medium>>(pulsed_beam);

    std::string mode = "sweep";
    dispersion_executor_gvd = DispersionExecutorGVD<PulsedBeam<Medium>>(pulsed_beam, mode);

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

            fourier_executor.forward();

            //diffraction_executor.process(dz);

            //dispersion_executor_full.process(dz);



            fourier_executor.backward();

            dispersion_executor_gvd.process(dz);

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

//
// Created by vasilyev on 28.06.2019.
//

#include "propagator.h"


template<template<typename, typename...> class PulsedBeam, typename Medium>
Propagator<PulsedBeam<Medium>>::Propagator(
        std::map<std::string, std::string>& args,
        PulsedBeam<Medium>& _pulsed_beam,
        size_t _n_z,
        double _dz,
        size_t _print_current_state_every,
        size_t _save_field_every):
            pulsed_beam(_pulsed_beam)
          , n_z(_n_z)
          , dz(_dz)
          , print_current_state_every(_print_current_state_every)
          , save_field_every(_save_field_every)
        {

      track_info = {{"n_z", (double)n_z},
                    {"dz", dz}};
      logger = Logger<PulsedBeam<Medium>>(args, pulsed_beam, track_info);

    logger.save_initial_parameters_to_pdf(true, true);
    logger.save_initial_parameters_to_yml();




}

template<template<typename, typename...> class PulsedBeam, typename Medium>
Propagator<PulsedBeam<Medium>>::~Propagator() = default;



template<template<typename, typename...> class PulsedBeam, typename Medium>
void Propagator<PulsedBeam<Medium>>::propagate() {
    /*
     * Main cycle
     */
    double z = 0.0;
    for (int step = 0; step < n_z + 1; ++step) {
        if (step) {
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

    //logger.save_states_to_csv();
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

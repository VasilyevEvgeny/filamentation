//
// Created by vasilyev on 28.06.2019.
//

#include "propagator.h"
#include "manager.h"

template<template<typename, typename...> class PulsedBeam, typename Medium>
Propagator<PulsedBeam<Medium>>::Propagator(
        std::map<std::string, std::string>& args,
        PulsedBeam<Medium>& _pulsed_beam,
        size_t _n_z,
        double _dz):
            pulsed_beam(_pulsed_beam)
          , n_z(_n_z)
          , dz(_dz)
        {

    Manager manager(args);

    std::map<std::string, double> track_info = {{"n_z", (double)n_z},
                                                {"dz", dz}};
    Logger<PulsedBeam<Medium>> logger(pulsed_beam, track_info);

    logger.save_initial_parameters_to_pdf(manager.current_results_dir, true, false);
    logger.save_initial_parameters_to_yml(manager.current_results_dir);


    /*
     * Main cycle
     */
    for (int step = 0; step < n_z; ++step) {

        pulsed_beam.save_field(step, manager.field_dir);

    }


}

template<template<typename, typename...> class PulsedBeam, typename Medium>
Propagator<PulsedBeam<Medium>>::~Propagator() = default;


template class Propagator<Gauss<SiO2>>;
template class Propagator<Gauss<CaF2>>;
template class Propagator<Gauss<LiF>>;
template class Propagator<Ring<SiO2>>;
template class Propagator<Ring<CaF2>>;
template class Propagator<Ring<LiF>>;
template class Propagator<Vortex<SiO2>>;
template class Propagator<Vortex<CaF2>>;
template class Propagator<Vortex<LiF>>;
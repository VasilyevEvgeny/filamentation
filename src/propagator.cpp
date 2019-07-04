//
// Created by vasilyev on 28.06.2019.
//

#include "propagator.h"
#include "manager.h"

template<template<typename, typename...> class PulsedBeam, typename Medium>
Propagator<PulsedBeam<Medium>>::Propagator(std::map<std::string, std::string>& args, PulsedBeam<Medium>& _pulsed_beam):
          pulsed_beam(_pulsed_beam)
        {

    Manager manager(args);
    Logger<PulsedBeam<Medium>> logger(pulsed_beam);



    logger.save_initial_parameters(manager.current_results_dir, true, false);

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
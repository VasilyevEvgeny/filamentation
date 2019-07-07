//
// Created by vasilyev on 30.06.2019.
//

#include "logger.h"

template<template<typename, typename...> class PulsedBeam, typename Medium>
Logger<PulsedBeam<Medium>>::Logger(PulsedBeam<Medium>& _pulsed_beam, std::map<std::string, double>& _track_info) :
  pulsed_beam(_pulsed_beam)
  , track_info(_track_info) {


}

template<template<typename, typename...> class PulsedBeam, typename Medium>
Logger<PulsedBeam<Medium>>::~Logger() = default;


template class Logger<Gauss<SiO2>>;
template class Logger<Gauss<CaF2>>;
template class Logger<Gauss<LiF>>;
template class Logger<Ring<SiO2>>;
template class Logger<Ring<CaF2>>;
template class Logger<Ring<LiF>>;
template class Logger<Vortex<SiO2>>;
template class Logger<Vortex<CaF2>>;
template class Logger<Vortex<LiF>>;
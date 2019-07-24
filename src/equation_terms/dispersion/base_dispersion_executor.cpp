//
// Created by vasilyev on 23.07.2019.
//

#include "base_dispersion_executor.h"

template<template<typename, typename...> class PulsedBeam, typename Medium>
BaseDispersionExecutor<PulsedBeam<Medium>>::BaseDispersionExecutor() = default;


template<template<typename, typename...> class PulsedBeam, typename Medium>
BaseDispersionExecutor<PulsedBeam<Medium>>::BaseDispersionExecutor(PulsedBeam<Medium>* _pulsed_beam) :
        BaseTerm<PulsedBeam <Medium>>(_pulsed_beam) {


}

template<template<typename, typename...> class PulsedBeam, typename Medium>
BaseDispersionExecutor<PulsedBeam<Medium>>::~BaseDispersionExecutor() = default;


template class BaseDispersionExecutor<Gauss<SiO2>>;
template class BaseDispersionExecutor<Gauss<CaF2>>;
template class BaseDispersionExecutor<Gauss<LiF>>;
template class BaseDispersionExecutor<Ring<SiO2>>;
template class BaseDispersionExecutor<Ring<CaF2>>;
template class BaseDispersionExecutor<Ring<LiF>>;
template class BaseDispersionExecutor<Vortex<SiO2>>;
template class BaseDispersionExecutor<Vortex<CaF2>>;
template class BaseDispersionExecutor<Vortex<LiF>>;



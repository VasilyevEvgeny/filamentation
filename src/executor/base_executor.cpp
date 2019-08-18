//
// Created by vasilyev on 27.07.2019.
//

#include "base_executor.h"

template<template<typename, typename...> class PulsedBeam, typename Medium>
BaseExecutor<PulsedBeam<Medium>>::BaseExecutor() = default;


template<template<typename, typename...> class PulsedBeam, typename Medium>
BaseExecutor<PulsedBeam<Medium>>::BaseExecutor(std::shared_ptr<PulsedBeam<Medium>> _pulsed_beam)
: pulsed_beam(_pulsed_beam) {

}


template<template<typename, typename...> class PulsedBeam, typename Medium>
BaseExecutor<PulsedBeam<Medium>>::~BaseExecutor() = default;


template class BaseExecutor<Gauss<SiO2>>;
template class BaseExecutor<Gauss<CaF2>>;
template class BaseExecutor<Gauss<LiF>>;
template class BaseExecutor<Ring<SiO2>>;
template class BaseExecutor<Ring<CaF2>>;
template class BaseExecutor<Ring<LiF>>;
template class BaseExecutor<Vortex<SiO2>>;
template class BaseExecutor<Vortex<CaF2>>;
template class BaseExecutor<Vortex<LiF>>;

template class BaseExecutor<BasePulsedBeam<BaseMedium>>;
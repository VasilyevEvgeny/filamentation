//
// Created by vasilyev on 23.07.2019.
//

#include "base_dispersion.h"

template<template<typename, typename...> class PulsedBeam, typename Medium>
BaseDispersion<PulsedBeam<Medium>>::BaseDispersion() = default;


template<template<typename, typename...> class PulsedBeam, typename Medium>
BaseDispersion<PulsedBeam<Medium>>::BaseDispersion(std::shared_ptr<PulsedBeam<Medium>> _pulsed_beam, bool _T)
: BaseLinearTerm<PulsedBeam <Medium>>(_pulsed_beam, _T) {


}

template<template<typename, typename...> class PulsedBeam, typename Medium>
BaseDispersion<PulsedBeam<Medium>>::~BaseDispersion() = default;




template<template<typename, typename...> class PulsedBeam, typename Medium>
void BaseDispersion<PulsedBeam<Medium>>::process(double dz) {


}




template class BaseDispersion<Gauss<SiO2>>;
template class BaseDispersion<Gauss<CaF2>>;
template class BaseDispersion<Gauss<LiF>>;
template class BaseDispersion<Ring<SiO2>>;
template class BaseDispersion<Ring<CaF2>>;
template class BaseDispersion<Ring<LiF>>;
template class BaseDispersion<Vortex<SiO2>>;
template class BaseDispersion<Vortex<CaF2>>;
template class BaseDispersion<Vortex<LiF>>;



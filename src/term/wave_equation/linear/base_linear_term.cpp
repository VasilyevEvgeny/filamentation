//
// Created by vasilyev on 27.07.2019.
//

#include "base_linear_term.h"

template<template<typename, typename...> class PulsedBeam, typename Medium>
BaseLinearTerm<PulsedBeam<Medium>>::BaseLinearTerm() = default;


template<template<typename, typename...> class PulsedBeam, typename Medium>
BaseLinearTerm<PulsedBeam<Medium>>::BaseLinearTerm(PulsedBeam<Medium>* _pulsed_beam, bool _T)
: BaseTerm<PulsedBeam <Medium>>(_pulsed_beam, _T) {



}


template<template<typename, typename...> class PulsedBeam, typename Medium>
BaseLinearTerm<PulsedBeam<Medium>>::~BaseLinearTerm() = default;




template class BaseLinearTerm<Gauss<SiO2>>;
template class BaseLinearTerm<Ring<SiO2>>;
template class BaseLinearTerm<Vortex<SiO2>>;
template class BaseLinearTerm<Gauss<CaF2>>;
template class BaseLinearTerm<Ring<CaF2>>;
template class BaseLinearTerm<Vortex<CaF2>>;
template class BaseLinearTerm<Gauss<LiF>>;
template class BaseLinearTerm<Ring<LiF>>;
template class BaseLinearTerm<Vortex<LiF>>;

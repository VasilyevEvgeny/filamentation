//
// Created by vasilyev on 25.07.2019.
//

#include "base_nonlinear_term.h"

template<template<typename, typename...> class PulsedBeam, typename Medium>
BaseNonlinearTerm<PulsedBeam<Medium>>::BaseNonlinearTerm() = default;


template<template<typename, typename...> class PulsedBeam, typename Medium>
BaseNonlinearTerm<PulsedBeam<Medium>>::BaseNonlinearTerm(PulsedBeam<Medium>* _pulsed_beam) :
        BaseTerm<PulsedBeam <Medium>>(_pulsed_beam) {


}

template<template<typename, typename...> class PulsedBeam, typename Medium>
BaseNonlinearTerm<PulsedBeam<Medium>>::~BaseNonlinearTerm() = default;


template class BaseNonlinearTerm<Gauss<SiO2>>;
template class BaseNonlinearTerm<Gauss<CaF2>>;
template class BaseNonlinearTerm<Gauss<LiF>>;
template class BaseNonlinearTerm<Ring<SiO2>>;
template class BaseNonlinearTerm<Ring<CaF2>>;
template class BaseNonlinearTerm<Ring<LiF>>;
template class BaseNonlinearTerm<Vortex<SiO2>>;
template class BaseNonlinearTerm<Vortex<CaF2>>;
template class BaseNonlinearTerm<Vortex<LiF>>;



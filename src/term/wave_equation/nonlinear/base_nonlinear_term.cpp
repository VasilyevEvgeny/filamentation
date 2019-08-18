//
// Created by vasilyev on 25.07.2019.
//

#include "base_nonlinear_term.h"

template<template<typename, typename...> class PulsedBeam, typename Medium>
BaseNonlinearTerm<PulsedBeam<Medium>>::BaseNonlinearTerm() = default;


template<template<typename, typename...> class PulsedBeam, typename Medium>
BaseNonlinearTerm<PulsedBeam<Medium>>::BaseNonlinearTerm(std::shared_ptr<PulsedBeam<Medium>> _pulsed_beam, bool _T)
: BaseTerm<PulsedBeam <Medium>>(_pulsed_beam, _T)
, R_kerr_instant(0)
, R_kerr_instant_T(0)
, R_plasma(0)
, R_plasma_T(0)
, R_dissipation(0)
, R_bremsstrahlung(0)
, R_bremsstrahlung_T(0) {




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



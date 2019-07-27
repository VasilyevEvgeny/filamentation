//
// Created by vasilyev on 26.07.2019.
//

#include "kerr_instant.h"

#define base BaseTerm<PulsedBeam<Medium>>
#define base_nonlinear BaseNonlinearTerm<PulsedBeam<Medium>>
#define pb BaseTerm<PulsedBeam<Medium>>::pulsed_beam
#define medium BaseTerm<PulsedBeam<Medium>>::pulsed_beam->medium

template<template<typename, typename...> class PulsedBeam, typename Medium>
KerrInstant<PulsedBeam<Medium>>::KerrInstant() = default;


template<template<typename, typename...> class PulsedBeam, typename Medium>
KerrInstant<PulsedBeam<Medium>>::KerrInstant(PulsedBeam<Medium>* _pulsed_beam)
: BaseNonlinearTerm<PulsedBeam<Medium>>(_pulsed_beam) {

base::name = "kerr_instant";
base::formula = R"( + \frac{2 k_0^2}{n_0} n_2 I(r,t,z) A(r,t,z) )";
base_nonlinear::R = -medium->math_constants.M_COMPLEX_I * medium->k_0 * (1.0 - medium->g) * medium->n_2 * pb->i_0 / medium->n_0;
}

template<template<typename, typename...> class PulsedBeam, typename Medium>
KerrInstant<PulsedBeam<Medium>>::~KerrInstant() = default;


template class KerrInstant<Gauss<SiO2>>;
template class KerrInstant<Gauss<CaF2>>;
template class KerrInstant<Gauss<LiF>>;
template class KerrInstant<Ring<SiO2>>;
template class KerrInstant<Ring<CaF2>>;
template class KerrInstant<Ring<LiF>>;
template class KerrInstant<Vortex<SiO2>>;
template class KerrInstant<Vortex<CaF2>>;
template class KerrInstant<Vortex<LiF>>;
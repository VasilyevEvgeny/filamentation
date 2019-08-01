//
// Created by vasilyev on 01.08.2019.
//

#include "bremsstrahlung.h"

#define base BaseTerm<PulsedBeam<Medium>>
#define base_nonlinear BaseNonlinearTerm<PulsedBeam<Medium>>

#define ii BaseTerm<PulsedBeam<Medium>>::pulsed_beam->medium->math_constants.M_COMPLEX_I
#define m_e BaseTerm<PulsedBeam<Medium>>::pulsed_beam->medium->math_constants.m_e
#define eps_0 BaseTerm<PulsedBeam<Medium>>::pulsed_beam->medium->math_constants.epsilon_0
#define e BaseTerm<PulsedBeam<Medium>>::pulsed_beam->medium->math_constants.e
#define c BaseTerm<PulsedBeam<Medium>>::pulsed_beam->medium->math_constants.c

#define omega_0 BaseTerm<PulsedBeam<Medium>>::pulsed_beam->omega_0
#define i_0 BaseTerm<PulsedBeam<Medium>>::pulsed_beam->i_0

#define k_0 BaseTerm<PulsedBeam<Medium>>::pulsed_beam->medium->k_0
#define n_0 BaseTerm<PulsedBeam<Medium>>::pulsed_beam->medium->n_0
#define n_2 BaseTerm<PulsedBeam<Medium>>::pulsed_beam->medium->n_2
#define v_ei BaseTerm<PulsedBeam<Medium>>::pulsed_beam->medium->v_ei


template<template<typename, typename...> class PulsedBeam, typename Medium>
Bremsstrahlung<PulsedBeam<Medium>>::Bremsstrahlung() = default;

template<template<typename, typename...> class PulsedBeam, typename Medium>
Bremsstrahlung<PulsedBeam<Medium>>::Bremsstrahlung(PulsedBeam<Medium>* _pulsed_beam, bool _T)
: BaseNonlinearTerm<PulsedBeam<Medium>>(_pulsed_beam, _T) {

    base::name = "bremsstrahlung";

    base_nonlinear::R_bremsstrahlung = -pow(e, 2) * v_ei / (2.0 * k_0 * pow(c, 2) * m_e * eps_0 * omega_0);

    if (base::T) {
        base_nonlinear::R_bremsstrahlung_T = -ii * pow(e, 2) * v_ei / (k_0 * pow(c, 2) * m_e * eps_0 * pow(omega_0, 2));
    }

}

template<template<typename, typename...> class PulsedBeam, typename Medium>
Bremsstrahlung<PulsedBeam<Medium>>::~Bremsstrahlung() = default;



template class Bremsstrahlung<Gauss<SiO2>>;
template class Bremsstrahlung<Gauss<CaF2>>;
template class Bremsstrahlung<Gauss<LiF>>;
template class Bremsstrahlung<Ring<SiO2>>;
template class Bremsstrahlung<Ring<CaF2>>;
template class Bremsstrahlung<Ring<LiF>>;
template class Bremsstrahlung<Vortex<SiO2>>;
template class Bremsstrahlung<Vortex<CaF2>>;
template class Bremsstrahlung<Vortex<LiF>>;
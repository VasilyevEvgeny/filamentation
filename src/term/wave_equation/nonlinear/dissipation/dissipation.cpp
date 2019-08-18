//
// Created by vasilyev on 05.08.2019.
//

#include "dissipation.h"


#define base BaseTerm<PulsedBeam<Medium>>
#define base_nonlinear BaseNonlinearTerm<PulsedBeam<Medium>>

#define ii BaseTerm<PulsedBeam<Medium>>::pulsed_beam->medium->math_constants.M_COMPLEX_I
#define m_e BaseTerm<PulsedBeam<Medium>>::pulsed_beam->medium->math_constants.m_e
#define eps_0 BaseTerm<PulsedBeam<Medium>>::pulsed_beam->medium->math_constants.epsilon_0
#define e BaseTerm<PulsedBeam<Medium>>::pulsed_beam->medium->math_constants.e
#define c BaseTerm<PulsedBeam<Medium>>::pulsed_beam->medium->math_constants.c
#define h_bar BaseTerm<PulsedBeam<Medium>>::pulsed_beam->medium->math_constants.h_bar

#define omega_0 BaseTerm<PulsedBeam<Medium>>::pulsed_beam->omega_0
#define i_0 BaseTerm<PulsedBeam<Medium>>::pulsed_beam->i_0
#define dt BaseTerm<PulsedBeam<Medium>>::pulsed_beam->dt

#define k_0 BaseTerm<PulsedBeam<Medium>>::pulsed_beam->medium->k_0
#define n_0 BaseTerm<PulsedBeam<Medium>>::pulsed_beam->medium->n_0
#define n_2 BaseTerm<PulsedBeam<Medium>>::pulsed_beam->medium->n_2
#define v_ei BaseTerm<PulsedBeam<Medium>>::pulsed_beam->medium->v_ei
#define K BaseTerm<PulsedBeam<Medium>>::pulsed_beam->medium->K

template<template<typename, typename...> class PulsedBeam, typename Medium>
Dissipation<PulsedBeam<Medium>>::Dissipation() = default;

template<template<typename, typename...> class PulsedBeam, typename Medium>
Dissipation<PulsedBeam<Medium>>::Dissipation(std::shared_ptr<PulsedBeam<Medium>> _pulsed_beam)
: BaseNonlinearTerm<PulsedBeam<Medium>>(_pulsed_beam, false) {

    delta = base::pulsed_beam->medium->delta;

    base::name = "dissipation";

    base::formula = R"( - i k_0 (\alpha + \delta) A(r, t, z) )";

}

template<template<typename, typename...> class PulsedBeam, typename Medium>
Dissipation<PulsedBeam<Medium>>::~Dissipation() = default;



template<template<typename, typename...> class PulsedBeam, typename Medium>
void Dissipation<PulsedBeam<Medium>>::update_R_dissipation(double I, double Ne_increase_field) {
    double alpha = 0.0;
    if (I > base::pulsed_beam->medium->ionization.i_start) {
        alpha = Ne_increase_field * K * h_bar * omega_0 / (I * dt);
    }

    base_nonlinear::R_dissipation = -0.5 * (alpha + delta);
}


template class Dissipation<Gauss<SiO2>>;
template class Dissipation<Gauss<CaF2>>;
template class Dissipation<Gauss<LiF>>;
template class Dissipation<Ring<SiO2>>;
template class Dissipation<Ring<CaF2>>;
template class Dissipation<Ring<LiF>>;
template class Dissipation<Vortex<SiO2>>;
template class Dissipation<Vortex<CaF2>>;
template class Dissipation<Vortex<LiF>>;
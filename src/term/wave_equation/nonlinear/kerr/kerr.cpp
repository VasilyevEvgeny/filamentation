//
// Created by vasilyev on 26.07.2019.
//

#include "kerr.h"

#define base BaseTerm<PulsedBeam<Medium>>
#define base_nonlinear BaseNonlinearTerm<PulsedBeam<Medium>>

#define ii BaseTerm<PulsedBeam<Medium>>::pulsed_beam->medium->math_constants.M_COMPLEX_I
#define m_e BaseTerm<PulsedBeam<Medium>>::pulsed_beam->medium->math_constants.m_e
#define eps_0 BaseTerm<PulsedBeam<Medium>>::pulsed_beam->medium->math_constants.epsilon_0
#define e BaseTerm<PulsedBeam<Medium>>::pulsed_beam->medium->math_constants.e

#define omega_0 BaseTerm<PulsedBeam<Medium>>::pulsed_beam->omega_0
#define i_0 BaseTerm<PulsedBeam<Medium>>::pulsed_beam->i_0

#define k_0 BaseTerm<PulsedBeam<Medium>>::pulsed_beam->medium->k_0
#define n_0 BaseTerm<PulsedBeam<Medium>>::pulsed_beam->medium->n_0
#define n_2 BaseTerm<PulsedBeam<Medium>>::pulsed_beam->medium->n_2


template<template<typename, typename...> class PulsedBeam, typename Medium>
Kerr<PulsedBeam<Medium>>::Kerr() = default;


template<template<typename, typename...> class PulsedBeam, typename Medium>
Kerr<PulsedBeam<Medium>>::Kerr(PulsedBeam<Medium>* _pulsed_beam, double _g, bool _T)
: BaseNonlinearTerm<PulsedBeam<Medium>>(_pulsed_beam, _T)
, g(_g) {

    base::name = "kerr";

    if (g == 0) {
        base::formula = R"( + \frac{2 k_0^2}{n_0} n_2 I(r,t,z) A(r,t,z) )";
        if (base::T) {
            base::formula = R"( + \hat{T} \frac{2 k_0^2}{n_0} n_2 I(r,t,z) A(r,t,z) )";
        }
    }
    else if (g == 1) {
        base::formula = R"( + \frac{2 k_0^2}{n_0} n_2 \int\limits_{0}^{+\infty} H(\tau) I(r, t - \tau) d\tau )";
        if (base::T) {
            base::formula = R"( + \hat{T} \frac{2 k_0^2}{n_0} n_2 \int\limits_{0}^{+\infty} H(\tau) I(r, t - \tau) d\tau )";
        }
    }
    else {
        base::formula = R"( + \frac{2 k_0^2}{n_0} (1 - g) n_2 I(r,t,z) A(r,t,z) + g n_2 \int\limits_{0}^{+\infty} H(\tau) I(r, t - \tau) d\tau )";
        if (base::T) {
            base::formula = R"( + \hat{T} \biggl[ \frac{2 k_0^2}{n_0} (1 - g) n_2 I(r,t,z) A(r,t,z) + g n_2 \int\limits_{0}^{+\infty} H(\tau) I(r, t - \tau) d\tau \biggr] )";
        }
    }

    base_nonlinear::R_kerr_instant = -ii * k_0 * (1.0 - g) * n_2 / n_0;
    if (base::T) {
        base_nonlinear::R_kerr_instant_T = -k_0 * (1.0 - g) * n_2 / (n_0 * omega_0);
    }

}

template<template<typename, typename...> class PulsedBeam, typename Medium>
Kerr<PulsedBeam<Medium>>::~Kerr() = default;


template class Kerr<Gauss<SiO2>>;
template class Kerr<Gauss<CaF2>>;
template class Kerr<Gauss<LiF>>;
template class Kerr<Ring<SiO2>>;
template class Kerr<Ring<CaF2>>;
template class Kerr<Ring<LiF>>;
template class Kerr<Vortex<SiO2>>;
template class Kerr<Vortex<CaF2>>;
template class Kerr<Vortex<LiF>>;
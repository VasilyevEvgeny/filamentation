//
// Created by vasilyev on 31.07.2019.
//

#include "plasma.h"

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
Plasma<PulsedBeam<Medium>>::Plasma() = default;


template<template<typename, typename...> class PulsedBeam, typename Medium>
Plasma<PulsedBeam<Medium>>::Plasma(std::shared_ptr<PulsedBeam<Medium>> _pulsed_beam, bool _T)
: BaseNonlinearTerm<PulsedBeam<Medium>>(_pulsed_beam, _T) {

    base::name = "plasma";

    base_nonlinear::R_plasma = ii * pow(e, 2) * k_0 / (2.0 * m_e * pow(omega_0 * n_0, 2) * eps_0);

    if (base::T) {
        base_nonlinear::R_plasma_T = -pow(e, 2) * k_0 / (2.0 * m_e * pow(omega_0, 3) * pow(n_0, 2) * eps_0);
    }


    if (!base:: T) {
        base::formula = R"( + \frac{2 k_0^2}{n_0} \Delta n_{pl} A(r, t, z) )";
    }
    else {
        base::formula = R"( + \hat{T}^{-1} \frac{2 k_0^2}{n_0} \Delta n_{pl} A(r, t, z) )";
    }
}


template<template<typename, typename...> class PulsedBeam, typename Medium>
Plasma<PulsedBeam<Medium>>::~Plasma() = default;


template class Plasma<Gauss<SiO2>>;
template class Plasma<Gauss<CaF2>>;
template class Plasma<Gauss<LiF>>;
template class Plasma<Ring<SiO2>>;
template class Plasma<Ring<CaF2>>;
template class Plasma<Ring<LiF>>;
template class Plasma<Vortex<SiO2>>;
template class Plasma<Vortex<CaF2>>;
template class Plasma<Vortex<LiF>>;

template class Plasma<BasePulsedBeam<BaseMedium>>;
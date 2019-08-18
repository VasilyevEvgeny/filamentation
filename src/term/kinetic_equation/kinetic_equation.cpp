//
// Created by vasilyev on 05.08.2019.
//

#include "kinetic_equation.h"

#define base BaseTerm<PulsedBeam<Medium>>


template<template<typename, typename...> class PulsedBeam, typename Medium>
KineticEquation<PulsedBeam<Medium>>::KineticEquation() = default;


template<template<typename, typename...> class PulsedBeam, typename Medium>
KineticEquation<PulsedBeam<Medium>>::KineticEquation(std::shared_ptr<PulsedBeam<Medium>> _pulsed_beam, double _v_i_const, double _beta)
: BaseTerm<PulsedBeam<Medium>>(_pulsed_beam, false)
, v_i_const(_v_i_const)
, beta(_beta){

    base::name = "kinetic_equation";

    base::formula = R"( \frac{\partial N_e(r,t)}{\partial t} =& \ R_E \Bigl[ N_0 - N_e(r,t) \Bigr] + \nu_i N_e(r,t) - \beta N_e(r,t) )";

}

template<template<typename, typename...> class PulsedBeam, typename Medium>
KineticEquation<PulsedBeam<Medium>>::~KineticEquation() = default;




template<template<typename, typename...> class PulsedBeam, typename Medium>
double KineticEquation<PulsedBeam<Medium>>::calculate_plasma_increase_full(double I_current, double Ne_current, double R) {
    double N0 = base::pulsed_beam->medium->N_0;
    double dt = base::pulsed_beam->dt;

    double summ = v_i_const * I_current - R - beta;

    if (summ != 0.0) {
        return (Ne_current + R * N0 / summ) * (exp(summ * dt) - 1.0);
    }
    else {
        return 0.0;
    }
}


template<template<typename, typename...> class PulsedBeam, typename Medium>
double KineticEquation<PulsedBeam<Medium>>::calculate_plasma_increase_field(double Ne, double R) {
    double N0 = base::pulsed_beam->medium->N_0;
    double dt = base::pulsed_beam->dt;

    return (N0 - Ne) * (1.0 - exp(-R * dt));
}



template class KineticEquation<Gauss<SiO2>>;
template class KineticEquation<Gauss<CaF2>>;
template class KineticEquation<Gauss<LiF>>;
template class KineticEquation<Ring<SiO2>>;
template class KineticEquation<Ring<CaF2>>;
template class KineticEquation<Ring<LiF>>;
template class KineticEquation<Vortex<SiO2>>;
template class KineticEquation<Vortex<CaF2>>;
template class KineticEquation<Vortex<LiF>>;

template class KineticEquation<BasePulsedBeam<BaseMedium>>;
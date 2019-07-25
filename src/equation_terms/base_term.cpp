//
// Created by vasilyev on 11.07.2019.
//

#include "base_term.h"

template<template<typename, typename...> class PulsedBeam, typename Medium>
BaseTerm<PulsedBeam<Medium>>::BaseTerm() = default;


template<template<typename, typename...> class PulsedBeam, typename Medium>
BaseTerm<PulsedBeam<Medium>>::BaseTerm(PulsedBeam<Medium>* _pulsed_beam) :
pulsed_beam(_pulsed_beam) {
    std::cout << "ADDRED OF PULSED BEAM IN BASE TERM: " << &(*pulsed_beam) << std::endl;
}


template<template<typename, typename...> class PulsedBeam, typename Medium>
void BaseTerm<PulsedBeam<Medium>>::process(double dz) {

}


template class BaseTerm<Gauss<SiO2>>;
template class BaseTerm<Gauss<CaF2>>;
template class BaseTerm<Gauss<LiF>>;
template class BaseTerm<Ring<SiO2>>;
template class BaseTerm<Ring<CaF2>>;
template class BaseTerm<Ring<LiF>>;
template class BaseTerm<Vortex<SiO2>>;
template class BaseTerm<Vortex<CaF2>>;
template class BaseTerm<Vortex<LiF>>;
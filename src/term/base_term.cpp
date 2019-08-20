//
// Created by vasilyev on 11.07.2019.
//

#include "base_term.h"

//template<template<typename, typename...> class PulsedBeam, typename Medium>
BaseTerm::BaseTerm() = default;


//template<template<typename, typename...> class PulsedBeam, typename Medium>
BaseTerm::BaseTerm(std::shared_ptr<BasePulsedBeam>& _pulsed_beam, bool _T)
: pulsed_beam(_pulsed_beam)
, T(_T){
}


//template<template<typename, typename...> class PulsedBeam, typename Medium>
BaseTerm::~BaseTerm() = default;

//
//
//template class BaseTerm<Gauss<SiO2>>;
//template class BaseTerm<Gauss<CaF2>>;
//template class BaseTerm<Gauss<LiF>>;
//template class BaseTerm<Ring<SiO2>>;
//template class BaseTerm<Ring<CaF2>>;
//template class BaseTerm<Ring<LiF>>;
//template class BaseTerm<Vortex<SiO2>>;
//template class BaseTerm<Vortex<CaF2>>;
//template class BaseTerm<Vortex<LiF>>;
//
//template class BaseTerm<BasePulsedBeam<BaseMedium>>;
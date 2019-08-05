//
// Created by vasilyev on 01.08.2019.
//

#ifndef FILAMENTATION_BREMSSTRAHLUNG_H
#define FILAMENTATION_BREMSSTRAHLUNG_H

#include "term/wave_equation/nonlinear/base_nonlinear_term.h"

template<typename T> class Bremsstrahlung;

template<template<typename, typename...> class PulsedBeam, typename Medium>
class Bremsstrahlung<PulsedBeam<Medium>>: public BaseNonlinearTerm<PulsedBeam<Medium>>  {
public:
    Bremsstrahlung();
    explicit Bremsstrahlung(PulsedBeam<Medium>* _pulsed_beam, bool _T);

    ~Bremsstrahlung();

};


#endif //FILAMENTATION_BREMSSTRAHLUNG_H

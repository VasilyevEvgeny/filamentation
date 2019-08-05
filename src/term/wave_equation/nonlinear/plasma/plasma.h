//
// Created by vasilyev on 31.07.2019.
//

#ifndef FILAMENTATION_PLASMA_H
#define FILAMENTATION_PLASMA_H


#include "term/wave_equation/nonlinear/base_nonlinear_term.h"

template<typename T> class Plasma;

template<template<typename, typename...> class PulsedBeam, typename Medium>
class Plasma<PulsedBeam<Medium>>: public BaseNonlinearTerm<PulsedBeam<Medium>>  {
public:
    Plasma();
    explicit Plasma(PulsedBeam<Medium>* _pulsed_beam, bool _T);

    ~Plasma();
};




#endif //FILAMENTATION_PLASMA_H

//
// Created by vasilyev on 26.07.2019.
//

#ifndef FILAMENTATION_KERRINSTANT_H
#define FILAMENTATION_KERRINSTANT_H


#include "../base_nonlinear_term.h"

template<typename T> class Kerr;

template<template<typename, typename...> class PulsedBeam, typename Medium>
class Kerr<PulsedBeam<Medium>>: public BaseNonlinearTerm<PulsedBeam<Medium>>  {
public:
    Kerr();
    explicit Kerr(PulsedBeam<Medium>* _pulsed_beam, double _g, bool _T);

    double g;

    ~Kerr();
};


#endif //FILAMENTATION_KERRINSTANT_H

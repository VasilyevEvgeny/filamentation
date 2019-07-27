//
// Created by vasilyev on 26.07.2019.
//

#ifndef FILAMENTATION_KERRINSTANT_H
#define FILAMENTATION_KERRINSTANT_H


#include "../base_nonlinear_term.h"

template<typename T> class KerrInstant;

template<template<typename, typename...> class PulsedBeam, typename Medium>
class KerrInstant<PulsedBeam<Medium>>: public BaseNonlinearTerm<PulsedBeam<Medium>>  {
public:
    KerrInstant();
    explicit KerrInstant(PulsedBeam<Medium>* _pulsed_beam);

    ~KerrInstant();
};


#endif //FILAMENTATION_KERRINSTANT_H

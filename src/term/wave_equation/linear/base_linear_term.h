//
// Created by vasilyev on 27.07.2019.
//

#ifndef FILAMENTATION_BASELINEARTERM_H
#define FILAMENTATION_BASELINEARTERM_H

#include "term/base_term.h"

template<typename T> class BaseLinearTerm;

template<template<typename, typename...> class PulsedBeam, typename Medium>
class BaseLinearTerm<PulsedBeam<Medium>> : public BaseTerm<PulsedBeam<Medium>> {
public:
    BaseLinearTerm();
    explicit BaseLinearTerm(PulsedBeam<Medium>* _pulsed_beam, bool _T);

    virtual ~BaseLinearTerm();

    virtual void process(double dz) = 0;
};


#endif //FILAMENTATION_BASELINEARTERM_H

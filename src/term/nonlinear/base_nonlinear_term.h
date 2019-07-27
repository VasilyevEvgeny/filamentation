//
// Created by vasilyev on 25.07.2019.
//

#ifndef FILAMENTATION_BASENONLINEARTERM_H
#define FILAMENTATION_BASENONLINEARTERM_H

#include "../base_term.h"

template<typename T> class BaseNonlinearTerm;

template<template<typename, typename...> class PulsedBeam, typename Medium>
class BaseNonlinearTerm<PulsedBeam<Medium>> : public BaseTerm<PulsedBeam<Medium>> {
public:
    BaseNonlinearTerm();
    explicit BaseNonlinearTerm(PulsedBeam<Medium>* _pulsed_beam);

    ~BaseNonlinearTerm();

    std::complex<double> R;

};


#endif //FILAMENTATION_BASENONLINEARTERM_H

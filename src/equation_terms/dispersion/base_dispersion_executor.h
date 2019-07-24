//
// Created by vasilyev on 23.07.2019.
//

#ifndef FILAMENTATION_DISPERSIONEXECUTOR_H
#define FILAMENTATION_DISPERSIONEXECUTOR_H

#include "equation_terms/base_term.h"

template<typename T> class BaseDispersionExecutor;

template<template<typename, typename...> class PulsedBeam, typename Medium>
class BaseDispersionExecutor<PulsedBeam<Medium>> : public BaseTerm<PulsedBeam<Medium>> {
public:
    BaseDispersionExecutor();
    explicit BaseDispersionExecutor(PulsedBeam<Medium>* _pulsed_beam);

    ~BaseDispersionExecutor();
};


#endif //FILAMENTATION_DISPERSIONEXECUTOR_H

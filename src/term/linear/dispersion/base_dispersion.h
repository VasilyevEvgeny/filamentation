//
// Created by vasilyev on 23.07.2019.
//

#ifndef FILAMENTATION_DISPERSIONEXECUTOR_H
#define FILAMENTATION_DISPERSIONEXECUTOR_H

#include "../base_linear_term.h"

template<typename T> class BaseDispersion;

template<template<typename, typename...> class PulsedBeam, typename Medium>
class BaseDispersion<PulsedBeam<Medium>> : public BaseLinearTerm<PulsedBeam<Medium>> {
public:
    BaseDispersion();
    explicit BaseDispersion(PulsedBeam<Medium>* _pulsed_beam);

    ~BaseDispersion();

    void process(double dz) override;
};


#endif //FILAMENTATION_DISPERSIONEXECUTOR_H

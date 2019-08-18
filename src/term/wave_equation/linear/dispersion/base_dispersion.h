//
// Created by vasilyev on 23.07.2019.
//

#ifndef FILAMENTATION_DISPERSIONEXECUTOR_H
#define FILAMENTATION_DISPERSIONEXECUTOR_H

#include "term/wave_equation/linear/base_linear_term.h"

template<typename T> class BaseDispersion;

template<template<typename, typename...> class PulsedBeam, typename Medium>
class BaseDispersion<PulsedBeam<Medium>> : public BaseLinearTerm<PulsedBeam<Medium>> {
public:
    BaseDispersion();
    explicit BaseDispersion(std::shared_ptr<PulsedBeam<Medium>> _pulsed_beam, bool _T);

    ~BaseDispersion();

    void process(double dz) override;
};


#endif //FILAMENTATION_DISPERSIONEXECUTOR_H

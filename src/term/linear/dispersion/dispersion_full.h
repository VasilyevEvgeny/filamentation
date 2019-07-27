//
// Created by vasilyev on 23.07.2019.
//

#ifndef FILAMENTATION_DISPERSIONEXECUTORFULL_H
#define FILAMENTATION_DISPERSIONEXECUTORFULL_H

#include "base_dispersion.h"

template<typename T> class DispersionFull;

template<template<typename, typename...> class PulsedBeam, typename Medium>
class DispersionFull<PulsedBeam<Medium>> : public BaseDispersion<PulsedBeam<Medium>> {
public:
    DispersionFull();
    explicit DispersionFull(PulsedBeam<Medium>* _pulsed_beam);

    ~DispersionFull();

    void process(double dz) override;
};


#endif //FILAMENTATION_DISPERSIONEXECUTORFULL_H

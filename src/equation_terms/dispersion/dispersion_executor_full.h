//
// Created by vasilyev on 23.07.2019.
//

#ifndef FILAMENTATION_DISPERSIONEXECUTORFULL_H
#define FILAMENTATION_DISPERSIONEXECUTORFULL_H

#include "base_dispersion_executor.h"

template<typename T> class DispersionExecutorFull;

template<template<typename, typename...> class PulsedBeam, typename Medium>
class DispersionExecutorFull<PulsedBeam<Medium>> : public BaseDispersionExecutor<PulsedBeam<Medium>> {
public:
    DispersionExecutorFull();
    DispersionExecutorFull(PulsedBeam<Medium>* _pulsed_beam);

    ~DispersionExecutorFull();

    void process(double dz);
};


#endif //FILAMENTATION_DISPERSIONEXECUTORFULL_H

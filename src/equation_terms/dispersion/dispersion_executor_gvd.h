//
// Created by vasilyev on 24.07.2019.
//

#ifndef FILAMENTATION_DISPERSIONEXECUTORGVD_H
#define FILAMENTATION_DISPERSIONEXECUTORGVD_H


#include "base_dispersion_executor.h"

template<typename T> class DispersionExecutorGVD;

template<template<typename, typename...> class PulsedBeam, typename Medium>
class DispersionExecutorGVD<PulsedBeam<Medium>> : public BaseDispersionExecutor<PulsedBeam<Medium>>  {
public:
    DispersionExecutorGVD();
    DispersionExecutorGVD(PulsedBeam<Medium>* _pulsed_beam, std::string& mode);

    ~DispersionExecutorGVD();

    std::string mode;

    void process(double dz);
    void process_fft(double dz);
    void process_sweep(double dz);


};


#endif //FILAMENTATION_DISPERSIONEXECUTORGVD_H

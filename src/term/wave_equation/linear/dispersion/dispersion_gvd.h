//
// Created by vasilyev on 24.07.2019.
//

#ifndef FILAMENTATION_DISPERSIONEXECUTORGVD_H
#define FILAMENTATION_DISPERSIONEXECUTORGVD_H


#include "base_dispersion.h"

template<typename T> class DispersionGVD;

template<template<typename, typename...> class PulsedBeam, typename Medium>
class DispersionGVD<PulsedBeam<Medium>> : public BaseDispersion<PulsedBeam<Medium>>  {
public:
    DispersionGVD();
    DispersionGVD(PulsedBeam<Medium>* _pulsed_beam, std::string& mode, bool _T);

    ~DispersionGVD();

    std::string mode;

    void process(double dz);
    void process_fft(double dz);
    void process_sweep(double dz);


};


#endif //FILAMENTATION_DISPERSIONEXECUTORGVD_H

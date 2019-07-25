//
// Created by vasilyev on 16.07.2019.
//

#ifndef FILAMENTATION_DIFFRACTIONEXECUTOR_H
#define FILAMENTATION_DIFFRACTIONEXECUTOR_H


#include "base_term.h"
#include "../pulsed_beam/base_pulsed_beam/base_pulsed_beam.h"
#include "../medium/base_medium.h"

template<typename T> class DiffractionExecutor;

template<template<typename, typename...> class PulsedBeam, typename Medium>
class DiffractionExecutor<PulsedBeam<Medium>> : public BaseTerm<PulsedBeam<Medium>>{
public:
    DiffractionExecutor();
    explicit DiffractionExecutor(PulsedBeam<Medium>* _pulsed_beam);


    void process(double dz) override;

    ~DiffractionExecutor();

};


#endif //FILAMENTATION_DIFFRACTIONEXECUTOR_H

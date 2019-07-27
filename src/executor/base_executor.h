//
// Created by vasilyev on 27.07.2019.
//

#ifndef FILAMENTATION_BASEEXECUTOR_H
#define FILAMENTATION_BASEEXECUTOR_H

#include <vector>
#include <string>

#include "pulsed_beam/gauss.h"
#include "pulsed_beam/ring.h"
#include "pulsed_beam/vortex.h"

#include "medium/SiO2.h"
#include "medium/CaF2.h"
#include "medium/LiF.h"

template<typename T> class BaseExecutor;

template<template<typename, typename...> class PulsedBeam, typename Medium>
class BaseExecutor<PulsedBeam<Medium>> {
public:
    BaseExecutor();
    explicit BaseExecutor(PulsedBeam<Medium>* _pulsed_beam,
                          std::vector<std::string>& active_terms);
    virtual ~BaseExecutor();

    PulsedBeam<Medium>* pulsed_beam;

    std::vector<std::string> active_terms;

    virtual void execute(double dz) = 0;
};


#endif //FILAMENTATION_BASE_EXECUTOR_H

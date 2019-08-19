//
// Created by vasilyev on 27.07.2019.
//

#ifndef FILAMENTATION_BASEEXECUTOR_H
#define FILAMENTATION_BASEEXECUTOR_H

#include <vector>
#include <string>

#include "pulsed_beam/gauss/gauss.h"
#include "pulsed_beam/ring/ring.h"
#include "pulsed_beam/vortex/vortex.h"

#include "medium/materials/SiO2/SiO2.h"
#include "medium/materials/CaF2/CaF2.h"
#include "medium/materials/LiF/LiF.h"

template<typename T> class BaseExecutor;

template<template<typename, typename...> class PulsedBeam, typename Medium>
class BaseExecutor<PulsedBeam<Medium>> {
public:
    BaseExecutor();
    explicit BaseExecutor(std::shared_ptr<PulsedBeam<Medium>> _pulsed_beam);
    virtual ~BaseExecutor();

    std::shared_ptr<PulsedBeam<Medium>> pulsed_beam;

    virtual void execute(double dz) = 0;
};


#endif //FILAMENTATION_BASE_EXECUTOR_H

//
// Created by vasilyev on 28.06.2019.
//

#ifndef FILAMENTATION_PROPAGATOR_H
#define FILAMENTATION_PROPAGATOR_H

#include <map>
#include <string>
#include <chrono>
#include <memory>

#include "pulsed_beam/base_pulsed_beam.h"
#include "logger/logger.h"
#include "medium/materials/base_medium.h"
#include "manager/dir_manager/dir_manager.h"
#include "manager/config_manager/config_manager.h"

#include "term/wave_equation/linear/diffraction/diffraction.h"
#include "term/wave_equation/linear/dispersion/dispersion_full.h"
#include "term/wave_equation/linear/dispersion/dispersion_gvd.h"
#include "term/wave_equation/nonlinear/kerr/kerr.h"
#include "term/wave_equation/nonlinear/plasma/plasma.h"
#include "term/wave_equation/nonlinear/bremsstrahlung/bremsstrahlung.h"
#include "term/wave_equation/nonlinear/dissipation/dissipation.h"

#include "term/kinetic_equation/kinetic_equation.h"

#include "executor/linear_executor/linear_executor.h"
#include "executor/nonlinear_executor/nonlinear_executor.h"

template<typename T> class Propagator;

template<template<typename, typename...> class PulsedBeam, typename Medium>
class Propagator<PulsedBeam<Medium>> {
public:
    Propagator();
    explicit Propagator(ConfigManager& config_manager,
               std::shared_ptr<PulsedBeam<Medium>> _pulsed_beam);
    ~Propagator();

    ConfigManager config_manager;
    DirManager dir_manager;
    Postprocessor processor;
    Logger<PulsedBeam<Medium>, Postprocessor> logger;

    std::shared_ptr<PulsedBeam<Medium>> pulsed_beam;

    // executors
    std::shared_ptr<LinearExecutor<PulsedBeam<Medium>>> linear_executor;
    std::shared_ptr<NonlinearExecutor<PulsedBeam<Medium>>> nonlinear_executor;

    void propagate();

private:

};





#endif //FILAMENTATION_PROPAGATOR_H

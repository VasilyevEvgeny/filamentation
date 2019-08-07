//
// Created by vasilyev on 28.06.2019.
//

#ifndef FILAMENTATION_PROPAGATOR_H
#define FILAMENTATION_PROPAGATOR_H

#include <map>
#include <string>
#include <chrono>

#include "pulsed_beam/base_pulsed_beam/base_pulsed_beam.h"
#include "logger/logger.h"
#include "medium/base_medium.h"
#include "manager/dir_manager.h"
#include "manager/config_manager.h"

#include "term/wave_equation/linear/diffraction/diffraction.h"
#include "term/wave_equation/linear/dispersion/dispersion_full.h"
#include "term/wave_equation/linear/dispersion/dispersion_gvd.h"
#include "term/wave_equation/nonlinear/kerr/kerr.h"
#include "term/wave_equation/nonlinear/plasma/plasma.h"
#include "term/wave_equation/nonlinear/bremsstrahlung/bremsstrahlung.h"
#include "term/wave_equation/nonlinear/dissipation/dissipation.h"

#include "term/kinetic_equation/kinetic_equation.h"

#include "executor/linear_executor.h"
#include "executor/nonlinear_executor.h"

template<typename T> class Propagator;

template<template<typename, typename...> class PulsedBeam, typename Medium>
class Propagator<PulsedBeam<Medium>> {
public:
    Propagator();
    Propagator(ConfigManager& config_manager,
               PulsedBeam<Medium>& _pulsed_beam);
    ~Propagator();

    ConfigManager config_manager;
    DirManager dir_manager;
    Processor processor;
    Logger<PulsedBeam<Medium>, Processor> logger;

    PulsedBeam<Medium>* pulsed_beam;

    // linear terms
    Diffraction<PulsedBeam<Medium>> diffraction;
    DispersionFull<PulsedBeam<Medium>> dispersion_full;
    DispersionGVD<PulsedBeam<Medium>> dispersion_gvd;

    // nonlinear terms
    Kerr<PulsedBeam<Medium>> kerr;
    Plasma<PulsedBeam<Medium>> plasma;
    Bremsstrahlung<PulsedBeam<Medium>> bremsstrahlung;
    Dissipation<PulsedBeam<Medium>> dissipation;

    // executors
    LinearExecutor<PulsedBeam<Medium>> linear_executor;
    NonlinearExecutor<PulsedBeam<Medium>> nonlinear_executor;

    // containers for terms
    std::map<std::string, BaseLinearTerm<PulsedBeam<Medium>>*> linear_terms_pool;
    std::map<std::string, BaseNonlinearTerm<PulsedBeam<Medium>>*> nonlinear_terms_pool;
    std::vector<std::string> active_linear_terms;
    std::vector<std::string> active_nonlinear_terms;

    size_t n_z;
    size_t print_current_state_every;
    size_t save_field_every;

    std::map<std::string, double> track_info;



    void propagate();

private:

};





#endif //FILAMENTATION_PROPAGATOR_H

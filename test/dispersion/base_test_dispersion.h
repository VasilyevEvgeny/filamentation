//
// Created by vasilyev on 24.07.2019.
//

#ifndef FILAMENTATION_BASETESTDISPERSION_H
#define FILAMENTATION_BASETESTDISPERSION_H

#include <memory>

#include "medium/base_medium.h"
#include "medium/SiO2.h"
#include "medium/CaF2.h"
#include "medium/LiF.h"

#include "pulsed_beam/base_pulsed_beam/base_pulsed_beam.h"
#include "pulsed_beam/gauss.h"
#include "pulsed_beam/ring.h"
#include "pulsed_beam/vortex.h"

#include "equation_terms/base_term.h"
#include "fft/fft.h"
#include "equation_terms/dispersion/dispersion_executor_full.h"
#include "equation_terms/dispersion/dispersion_executor_gvd.h"
#include "logger/logger.h"
#include "functions.h"

#include "processor_dispersion.h"

template<typename T> class BaseTestDispersion;

template<template<typename, typename...> class PulsedBeam, typename Medium>
class BaseTestDispersion<PulsedBeam<Medium>> {
public:
    BaseTestDispersion();
    explicit BaseTestDispersion(PulsedBeam<Medium>& _pulsed_beam);
    virtual ~BaseTestDispersion() = 0;

    Manager manager;
    ProcessorDispersion processor_dispersion;

    size_t n_z;
    double dz;
    std::map<std::string, double> track_info;

    size_t save_field_every;
    size_t print_current_state_every;

    PulsedBeam<Medium>* pulsed_beam;
    Logger<PulsedBeam<Medium>, ProcessorDispersion> logger;

    std::map<std::string, std::string> initialize_args(std::string& _info);

    virtual void test() = 0;
};


#endif //FILAMENTATION_BASETESTDISPERSION_H

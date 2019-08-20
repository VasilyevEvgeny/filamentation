//
// Created by vasilyev on 24.07.2019.
//

#ifndef FILAMENTATION_BASETESTDISPERSION_H
#define FILAMENTATION_BASETESTDISPERSION_H

#include <memory>

#include "medium/material/base_medium.h"
#include "medium/material/SiO2/SiO2.h"
#include "medium/material/CaF2/CaF2.h"
#include "medium/material/LiF/LiF.h"

#include "pulsed_beam/base_pulsed_beam.h"
#include "pulsed_beam/gauss/gauss.h"
#include "pulsed_beam/ring/ring.h"
#include "pulsed_beam/vortex/vortex.h"

#include "equation_terms/base_term.h"
#include "fft/fft.h"
#include "equation_terms/dispersion/dispersion_executor_full.h"
#include "equation_terms/dispersion/dispersion_executor_gvd.h"
#include "saver/saver.h"
#include "misc/misc.h"

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

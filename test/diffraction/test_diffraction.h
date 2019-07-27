//
// Created by vasilyev on 17.07.2019.
//

#ifndef FILAMENTATION_TESTDIFFRACTION_H
#define FILAMENTATION_TESTDIFFRACTION_H

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
#include "term/linear/diffraction/diffraction.h"
#include "logger/logger.h"
#include "functions.h"

#include "processor_diffraction.h"



template<typename T> class TestDiffraction;

template<template<typename, typename...> class PulsedBeam, typename Medium>
class TestDiffraction<PulsedBeam<Medium>> {
public:
    explicit TestDiffraction(PulsedBeam<Medium>& _pulsed_beam);
    ~TestDiffraction();

    Manager manager;
    ProcessorDiffraction processor_diffraction;

    size_t n_z;
    double dz;
    std::map<std::string, double> track_info;

    size_t save_field_every;
    size_t print_current_state_every;

    PulsedBeam<Medium>* pulsed_beam;
    FourierExecutor<PulsedBeam<Medium>> fourier_executor;
    DiffractionExecutor<PulsedBeam<Medium>> diffraction_executor;

    Logger<PulsedBeam<Medium>, ProcessorDiffraction> logger;

    std::map<std::string, std::string> initialize_args(std::string& _info);


    void test();
};


#endif //FILAMENTATION_TESTDIFFRACTION_H

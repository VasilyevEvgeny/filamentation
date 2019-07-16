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
#include "manager.h"
#include "equation_terms/fourier_executor.h"

template<typename T> class Propagator;

template<template<typename, typename...> class PulsedBeam, typename Medium>
class Propagator<PulsedBeam<Medium>> {
public:
    Propagator(
            std::map<std::string, std::string>& args,
            PulsedBeam<Medium>& _pulsed_beam,
            size_t n_z,
            double dz,
            size_t _print_current_state_every,
            size_t _save_field_every);
    ~Propagator();


    PulsedBeam<Medium>* pulsed_beam;
    FourierExecutor<PulsedBeam<Medium>> fourier_executor;

    size_t n_z;
    double dz;
    size_t print_current_state_every;
    size_t save_field_every;

    std::map<std::string, double> track_info;
    Logger<PulsedBeam<Medium>> logger;

    void propagate();

private:

};





#endif //FILAMENTATION_PROPAGATOR_H

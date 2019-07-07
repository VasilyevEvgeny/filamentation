//
// Created by vasilyev on 28.06.2019.
//

#ifndef FILAMENTATION_PROPAGATOR_H
#define FILAMENTATION_PROPAGATOR_H

#include <map>
#include <string>

#include "pulsed_beam/base_pulsed_beam/base_pulsed_beam.h"
#include "logger/logger.h"
#include "medium/base_medium.h"

template<typename T> class Propagator;

template<template<typename, typename...> class PulsedBeam, typename Medium>
class Propagator<PulsedBeam<Medium>> {
public:
    Propagator(std::map<std::string, std::string>& args, PulsedBeam<Medium>&_pulsed_beam, size_t n_z, double dz);
    ~Propagator();


    PulsedBeam<Medium> pulsed_beam;
    size_t n_z;
    double dz;


private:

};


#endif //FILAMENTATION_PROPAGATOR_H

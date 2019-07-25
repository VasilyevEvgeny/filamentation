//
// Created by vasilyev on 11.07.2019.
//

#ifndef FILAMENTATION_BASETERM_H
#define FILAMENTATION_BASETERM_H

#include "../pulsed_beam/base_pulsed_beam/base_pulsed_beam.h"
#include "../pulsed_beam/gauss.h"
#include "../pulsed_beam/ring.h"
#include "../pulsed_beam/vortex.h"
#include "../medium/base_medium.h"
#include "../medium/SiO2.h"
#include "../medium/CaF2.h"
#include "../medium/LiF.h"


template<typename T> class BaseTerm;

template<template<typename, typename...> class PulsedBeam, typename Medium>
class BaseTerm<PulsedBeam<Medium>> {
public:
    BaseTerm();
    explicit BaseTerm(PulsedBeam<Medium>* _pulsed_beam);

    PulsedBeam<Medium>* pulsed_beam;

    std::string name;
    std::string formula;

    virtual void process(double dz);
};


#endif //FILAMENTATION_BASETERM_H

//
// Created by vasilyev on 11.07.2019.
//

#ifndef FILAMENTATION_BASETERM_H
#define FILAMENTATION_BASETERM_H

#include "pulsed_beam/base_pulsed_beam.h"
#include "pulsed_beam/gauss/gauss.h"
#include "pulsed_beam/ring/ring.h"
#include "pulsed_beam/vortex/vortex.h"
#include "medium/materials/base_medium.h"
#include "medium/materials/SiO2/SiO2.h"
#include "medium/materials/CaF2/CaF2.h"
#include "medium/materials//LiF/LiF.h"


template<typename T> class BaseTerm;

template<template<typename, typename...> class PulsedBeam, typename Medium>
class BaseTerm<PulsedBeam<Medium>> {
public:
    BaseTerm();
    explicit BaseTerm(std::shared_ptr<PulsedBeam<Medium>> _pulsed_beam, bool _T);
    virtual ~BaseTerm();

    std::shared_ptr<PulsedBeam<Medium>> pulsed_beam;

    bool T;

    std::string name;
    std::string formula;

};


#endif //FILAMENTATION_BASETERM_H

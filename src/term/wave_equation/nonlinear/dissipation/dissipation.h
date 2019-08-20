//
// Created by vasilyev on 05.08.2019.
//

#ifndef FILAMENTATION_DISSIPATION_H
#define FILAMENTATION_DISSIPATION_H

#include "term/wave_equation/nonlinear/base_nonlinear_term.h"

//template<typename T> class Dissipation;

//template<template<typename, typename...> class PulsedBeam, typename Medium>
class Dissipation : public BaseNonlinearTerm {
public:
    Dissipation();
    explicit Dissipation(std::shared_ptr<BasePulsedBeam>& _pulsed_beam);

    ~Dissipation();

    double delta;

    void update_R_dissipation(double I, double Ne_increase_field);
};


#endif //FILAMENTATION_DISSIPATION_H

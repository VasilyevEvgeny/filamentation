//
// Created by vasilyev on 27.07.2019.
//

#ifndef FILAMENTATION_NONLINEAREXECUTOR_H
#define FILAMENTATION_NONLINEAREXECUTOR_H

#include "base_executor.h"
#include "term/wave_equation/nonlinear/base_nonlinear_term.h"
#include "term/kinetic_equation/kinetic_equation.h"
#include "term/wave_equation/nonlinear/dissipation/dissipation.h"

#include <map>

template<typename T> class NonlinearExecutor;

template<template<typename, typename...> class PulsedBeam, typename Medium>
class NonlinearExecutor<PulsedBeam<Medium>> : public BaseExecutor<PulsedBeam<Medium>> {
public:
    NonlinearExecutor();
    explicit NonlinearExecutor(PulsedBeam<Medium>* _pulsed_beam,
                               std::vector<std::string>& _active_nonlinear_terms,
                               std::map<std::string, BaseNonlinearTerm<PulsedBeam<Medium>>*>& _nonlinear_terms_pool,
                               Dissipation<PulsedBeam<Medium>>* _dissipation);
    ~NonlinearExecutor();

    std::map<std::string, BaseNonlinearTerm<PulsedBeam<Medium>>*> nonlinear_terms_pool;

    // kinetic equation
    KineticEquation<PulsedBeam<Medium>> kinetic_equation;

    Dissipation<PulsedBeam<Medium>>* dissipation;

    void execute(double dz) override;
};


#endif //FILAMENTATION_NONLINEAREXECUTOR_H

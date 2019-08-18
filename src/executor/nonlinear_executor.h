//
// Created by vasilyev on 27.07.2019.
//

#ifndef FILAMENTATION_NONLINEAREXECUTOR_H
#define FILAMENTATION_NONLINEAREXECUTOR_H

#include "base_executor.h"
#include "term/wave_equation/nonlinear/base_nonlinear_term.h"
#include "term/kinetic_equation/kinetic_equation.h"
#include "term/wave_equation/nonlinear/dissipation/dissipation.h"
#include "term/wave_equation/nonlinear/kerr/kerr.h"
#include "term/wave_equation/nonlinear/plasma/plasma.h"
#include "term/wave_equation/nonlinear/bremsstrahlung/bremsstrahlung.h"
#include "term/wave_equation/nonlinear/dissipation/dissipation.h"

#include <map>
#include <memory>

template<typename T> class NonlinearExecutor;

template<template<typename, typename...> class PulsedBeam, typename Medium>
class NonlinearExecutor<PulsedBeam<Medium>> : public BaseExecutor<PulsedBeam<Medium>> {
public:
    NonlinearExecutor();
    explicit NonlinearExecutor(ConfigManager& _config_manager,
                               std::shared_ptr<PulsedBeam<Medium>> _pulsed_beam);
    ~NonlinearExecutor();

    ConfigManager config_manager;

    std::map<std::string, std::shared_ptr<BaseNonlinearTerm<PulsedBeam<Medium>>>> terms_pool;

    // nonlinear terms
    std::shared_ptr<Kerr<PulsedBeam<Medium>>> kerr;
    std::shared_ptr<Plasma<PulsedBeam<Medium>>> plasma;
    std::shared_ptr<Bremsstrahlung<PulsedBeam<Medium>>> bremsstrahlung;
    std::shared_ptr<Dissipation<PulsedBeam<Medium>>> dissipation;

    // kinetic equation
    std::shared_ptr<KineticEquation<PulsedBeam<Medium>>> kinetic_equation;

    void execute(double dz) override;
};


#endif //FILAMENTATION_NONLINEAREXECUTOR_H

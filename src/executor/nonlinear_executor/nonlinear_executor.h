//
// Created by vasilyev on 27.07.2019.
//

#ifndef FILAMENTATION_NONLINEAREXECUTOR_H
#define FILAMENTATION_NONLINEAREXECUTOR_H

#include <map>
#include <memory>

#include "executor/base_executor.h"
#include "term/wave_equation/nonlinear/base_nonlinear_term.h"
#include "term/kinetic_equation/kinetic_equation.h"
#include "term/wave_equation/nonlinear/dissipation/dissipation.h"
#include "term/wave_equation/nonlinear/kerr/kerr.h"
#include "term/wave_equation/nonlinear/plasma/plasma.h"
#include "term/wave_equation/nonlinear/bremsstrahlung/bremsstrahlung.h"
#include "term/wave_equation/nonlinear/dissipation/dissipation.h"


class NonlinearExecutor : public BaseExecutor {
public:
    NonlinearExecutor();
    explicit NonlinearExecutor(std::shared_ptr<BasePulsedBeam>& _pulsed_beam,
                               ConfigManager& _config_manager,
                               std::shared_ptr<Logger>& logger);
    ~NonlinearExecutor() override;

    ConfigManager config_manager;

    std::map<std::string, std::shared_ptr<BaseNonlinearTerm>> terms_pool;

    // nonlinear terms
    std::shared_ptr<Kerr> kerr;
    std::shared_ptr<Plasma> plasma;
    std::shared_ptr<Bremsstrahlung> bremsstrahlung;
    std::shared_ptr<Dissipation> dissipation;

    // kinetic equation
    std::shared_ptr<KineticEquation> kinetic_equation;

    void execute(double dz) override;
};


#endif //FILAMENTATION_NONLINEAREXECUTOR_H

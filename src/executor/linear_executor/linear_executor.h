//
// Created by vasilyev on 27.07.2019.
//

#ifndef FILAMENTATION_LINEAREXECUTOR_H
#define FILAMENTATION_LINEAREXECUTOR_H

#include <map>
#include <utility>
#include <memory>

#include "executor/base_executor.h"
#include "term/wave_equation/linear/base_linear_term.h"
#include "term/wave_equation/linear/diffraction/diffraction.h"
#include "term/wave_equation/linear/dispersion/dispersion_full.h"
#include "term/wave_equation/linear/dispersion/dispersion_gvd.h"
#include "executor/linear_executor/fft/fft.h"


class LinearExecutor : public BaseExecutor {
public:
    LinearExecutor();
    explicit LinearExecutor(std::shared_ptr<BasePulsedBeam>& _pulsed_beam,
                            ConfigManager& _config_manager,
                            std::shared_ptr<Logger>& logger);
    ~LinearExecutor() override;

    ConfigManager config_manager;

    FastFourierTransform fft;

    // linear terms
    std::shared_ptr<Diffraction> diffraction;
    std::shared_ptr<DispersionFull> dispersion_full;
    std::shared_ptr<DispersionGVD> dispersion_gvd;

    std::map<std::string, std::shared_ptr<BaseLinearTerm>> terms_pool;

    void execute(double dz) override;
};


#endif //FILAMENTATION_LINEAREXECUTOR_H

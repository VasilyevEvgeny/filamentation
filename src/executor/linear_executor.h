//
// Created by vasilyev on 27.07.2019.
//

#ifndef FILAMENTATION_LINEAREXECUTOR_H
#define FILAMENTATION_LINEAREXECUTOR_H

#include <map>
#include <utility>
#include <memory>

#include "base_executor.h"
#include "term/wave_equation/linear/base_linear_term.h"
#include "term/wave_equation/linear/diffraction/diffraction.h"
#include "term/wave_equation/linear/dispersion/dispersion_full.h"
#include "term/wave_equation/linear/dispersion/dispersion_gvd.h"
#include "fft/fft.h"

template<typename T> class LinearExecutor;

template<template<typename, typename...> class PulsedBeam, typename Medium>
class LinearExecutor<PulsedBeam<Medium>> : public BaseExecutor<PulsedBeam<Medium>> {
public:
    LinearExecutor();
    explicit LinearExecutor(ConfigManager& _config_manager,
                            std::shared_ptr<PulsedBeam<Medium>> _pulsed_beam);
    ~LinearExecutor();

    ConfigManager config_manager;

    FastFourierTransform<PulsedBeam<Medium>> fft;

    // linear terms
    std::shared_ptr<Diffraction<PulsedBeam<Medium>>> diffraction;
    std::shared_ptr<DispersionFull<PulsedBeam<Medium>>> dispersion_full;
    std::shared_ptr<DispersionGVD<PulsedBeam<Medium>>> dispersion_gvd;

    std::map<std::string, std::shared_ptr<BaseLinearTerm<PulsedBeam<Medium>>>> terms_pool;

    void execute(double dz) override;
};


#endif //FILAMENTATION_LINEAREXECUTOR_H

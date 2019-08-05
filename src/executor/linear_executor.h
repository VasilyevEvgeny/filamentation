//
// Created by vasilyev on 27.07.2019.
//

#ifndef FILAMENTATION_LINEAREXECUTOR_H
#define FILAMENTATION_LINEAREXECUTOR_H

#include <map>

#include "base_executor.h"
#include "term/wave_equation/linear/base_linear_term.h"
#include "fft/fft.h"

template<typename T> class LinearExecutor;

template<template<typename, typename...> class PulsedBeam, typename Medium>
class LinearExecutor<PulsedBeam<Medium>> : public BaseExecutor<PulsedBeam<Medium>> {
public:
    LinearExecutor();
    explicit LinearExecutor(PulsedBeam<Medium>* _pulsed_beam,
                            std::vector<std::string>& _active_linear_terms,
                            std::map<std::string, BaseLinearTerm<PulsedBeam<Medium>>*>& _linear_terms_pool);
    ~LinearExecutor();

    FastFourierTransform<PulsedBeam<Medium>> fft;

    std::map<std::string, BaseLinearTerm<PulsedBeam<Medium>>*> linear_terms_pool;

    void execute(double dz) override;
};


#endif //FILAMENTATION_LINEAREXECUTOR_H

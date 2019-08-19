//
// Created by vasilyev on 11.07.2019.
//

#ifndef FILAMENTATION_FASTFOURIERTRANSFORM_H
#define FILAMENTATION_FASTFOURIERTRANSFORM_H

#include "term/base_term.h"


template<typename T> class FastFourierTransform;

template<template<typename, typename...> class PulsedBeam, typename Medium>
class FastFourierTransform<PulsedBeam<Medium>> {
public:
    FastFourierTransform();
    explicit FastFourierTransform(std::shared_ptr<PulsedBeam<Medium>> _pulsed_beam);

    ~FastFourierTransform();

    std::shared_ptr<PulsedBeam<Medium>> pulsed_beam;

    void forward();
    void backward();


};


#endif //FILAMENTATION_FASTFOURIERTRANSFORM_H

//
// Created by vasilyev on 11.07.2019.
//

#ifndef FILAMENTATION_FOURIERTRANSFORMER_H
#define FILAMENTATION_FOURIERTRANSFORMER_H

#include "base_term.h"


template<typename T> class FourierExecutor;

template<template<typename, typename...> class PulsedBeam, typename Medium>
class FourierExecutor<PulsedBeam<Medium>> : public BaseTerm<PulsedBeam<Medium>>{
public:
    FourierExecutor();
    explicit FourierExecutor(PulsedBeam<Medium>* _pulsed_beam);

    ~FourierExecutor();

    void forward();
    void backward();


};


#endif //FILAMENTATION_FOURIERTRANSFORMER_H

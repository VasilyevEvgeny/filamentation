//
// Created by vasilyev on 24.07.2019.
//

#ifndef FILAMENTATIONTESTDISPERSIONFULL_H
#define FILAMENTATIONTESTDISPERSIONFULL_H

#include "base_test_dispersion.h"

template<typename T> class TestDispersionFull;

template<template<typename, typename...> class PulsedBeam, typename Medium>
class TestDispersionFull<PulsedBeam<Medium>> : public BaseTestDispersion<PulsedBeam<Medium>> {
public:
    TestDispersionFull();
    explicit TestDispersionFull(PulsedBeam<Medium>& _pulsed_beam);

    ~TestDispersionFull();


    std::string info;


    FourierExecutor<PulsedBeam<Medium>> fourier_executor;
    DispersionExecutorFull<PulsedBeam<Medium>> dispersion_executor_full;


    void test() override;
};


#endif //FILAMENTATION_TESTDISPERSIONFULL_H

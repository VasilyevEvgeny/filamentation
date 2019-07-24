//
// Created by vasilyev on 24.07.2019.
//

#ifndef FILAMENTATION_TESTDISPERSIONGVD_H
#define FILAMENTATION_TESTDISPERSIONGVD_H

#include "base_test_dispersion.h"

template<typename T> class TestDispersionGVD;

template<template<typename, typename...> class PulsedBeam, typename Medium>
class TestDispersionGVD<PulsedBeam<Medium>> : public BaseTestDispersion<PulsedBeam<Medium>> {
public:
    TestDispersionGVD();
    explicit TestDispersionGVD(PulsedBeam<Medium>& _pulsed_beam, std::string& _mode);

    ~TestDispersionGVD();


    std::string info;
    std::string mode;


    FourierExecutor<PulsedBeam<Medium>> fourier_executor;
    DispersionExecutorGVD<PulsedBeam<Medium>> dispersion_executor_gvd;


    void test() override;
};



#endif //FILAMENTATION_TESTDISPERSIONGVD_H

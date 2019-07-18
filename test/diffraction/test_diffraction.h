//
// Created by vasilyev on 17.07.2019.
//

#ifndef FILAMENTATION_TESTDIFFRACTION_H
#define FILAMENTATION_TESTDIFFRACTION_H


//#include "../../src/propagator.h"
#include "medium/base_medium.h"
#include "medium/LiF.h"

#include "pulsed_beam/base_pulsed_beam/base_pulsed_beam.h"
#include "pulsed_beam/gauss.h"
#include "pulsed_beam/ring.h"
#include "pulsed_beam/vortex.h"

#include "equation_terms/base_term.h"
#include "equation_terms/fourier_executor.h"
#include "equation_terms/diffraction_executor.h"
#include "logger/logger.h"


class TestDiffraction {
public:
    TestDiffraction();
    ~TestDiffraction();

    LiF medium;
    Vortex<LiF> pulsed_beam;

    Logger<Vortex<LiF>> logger;

    std::map<std::string, double> track_info;


    FourierExecutor<Vortex<LiF>> fourier_executor;
    DiffractionExecutor<Vortex<LiF>> diffraction_executor;

    size_t n_z;
    double dz;

    size_t save_field_every;
    size_t print_current_state_every;

    void test();
};


#endif //FILAMENTATION_TESTDIFFRACTION_H

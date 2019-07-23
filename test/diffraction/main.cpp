//
// Created by vasilyev on 17.07.2019.
//

#include <vector>

#include "gtest/gtest.h"
#include "test_diffraction.h"

// also CaF2, LiF
#define MEDIUM SiO2

int main() {

    double lambda_0 = generate_random_number(400, 3000) * 1e-9;
    size_t n_r = 512;
    size_t n_t = 1024;


    MEDIUM medium(lambda_0);

    double r_0 = generate_random_number(30, 150) * 1e-6;
    double t_0 = generate_random_number(20, 150) * 1e-15;




    // Gauss
    Gauss<MEDIUM> pulsed_beam_gauss = Gauss<MEDIUM>(medium,
                                                    lambda_0,
                                                    r_0,
                                                    n_r,
                                                    t_0,
                                                    n_t,
                                                    1);

    TestDiffraction<Gauss<MEDIUM>> test_diffraction_gauss = TestDiffraction<Gauss<MEDIUM>>(pulsed_beam_gauss);
    test_diffraction_gauss.test();



    // Vortex
    size_t M = generate_random_number(0, 5);
    size_t m = M;
    Vortex<MEDIUM> pulsed_beam_vortex = Vortex<MEDIUM>(medium,
                                                       lambda_0,
                                                       M,
                                                       m,
                                                       r_0,
                                                       n_r,
                                                       t_0,
                                                       n_t,
                                                       1);

    TestDiffraction<Vortex<MEDIUM>> test_diffraction_vortex = TestDiffraction<Vortex<MEDIUM>>(pulsed_beam_vortex);
    test_diffraction_vortex.test();

    return 0;
}

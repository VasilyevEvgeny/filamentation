//
// Created by vasilyev on 24.07.2019.
//


#include <vector>

#include "gtest/gtest.h"
#include "test_dispersion_full.h"
#include "test_dispersion_gvd.h"

// also CaF2, LiF
#define MEDIUM LiF

int main() {

    double lambda_0 = generate_random_number(400, 3000) * 1e-9;
    size_t n_r = 512;
    size_t n_t = 1024;


    MEDIUM medium(lambda_0);

    double r_0 = generate_random_number(30, 150) * 1e-6;
    double t_0 = generate_random_number(20, 50) * 1e-15;




    // Full
    Gauss<MEDIUM> pulsed_beam_1 = Gauss<MEDIUM>(medium,
                                                lambda_0,
                                                r_0,
                                                n_r,
                                                t_0,
                                                n_t,
                                                1);
    TestDispersionFull<Gauss<MEDIUM>> test_dispersion_full = TestDispersionFull<Gauss<MEDIUM>>(pulsed_beam_1);
    test_dispersion_full.test();

    // GVD FFT
    Gauss<MEDIUM> pulsed_beam_2 = Gauss<MEDIUM>(medium,
                                                lambda_0,
                                                r_0,
                                                n_r,
                                                t_0,
                                                n_t,
                                                1);
    std::string mode_fft = "fft";
    TestDispersionGVD<Gauss<MEDIUM>> test_dispersion_gvd_fft = TestDispersionGVD<Gauss<MEDIUM>>(pulsed_beam_2, mode_fft);
    test_dispersion_gvd_fft.test();

    // GVD sweep
    Gauss<MEDIUM> pulsed_beam_3 = Gauss<MEDIUM>(medium,
                                                lambda_0,
                                                r_0,
                                                n_r,
                                                t_0,
                                                n_t,
                                                1);
    std::string mode_sweep = "sweep";
    TestDispersionGVD<Gauss<MEDIUM>> test_dispersion_gvd_sweep = TestDispersionGVD<Gauss<MEDIUM>>(pulsed_beam_3, mode_sweep);
    test_dispersion_gvd_sweep.test();




    return 0;
}


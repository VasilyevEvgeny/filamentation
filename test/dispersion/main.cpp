//
// Created by vasilyev on 24.07.2019.
//

//
// Created by vasilyev on 17.07.2019.
//

#include <vector>

#include "gtest/gtest.h"
#include "test_dispersion_full.h"

// also CaF2, LiF
#define MEDIUM SiO2

int main() {

    double lambda_0 = generate_random_number(400, 3000) * 1e-9;
    size_t n_r = 512;
    size_t n_t = 1024;


    MEDIUM medium(lambda_0);

    double r_0 = generate_random_number(30, 150) * 1e-6;
    double t_0 = generate_random_number(20, 50) * 1e-15;




    // Gauss
    Gauss<MEDIUM> pulsed_beam = Gauss<MEDIUM>(medium,
                                                lambda_0,
                                                r_0,
                                                n_r,
                                                t_0,
                                                n_t,
                                                1);

    TestDispersionFull<Gauss<MEDIUM>> test_dispersion_full = TestDispersionFull<Gauss<MEDIUM>>(pulsed_beam);
    test_dispersion_full.test();





    return 0;
}


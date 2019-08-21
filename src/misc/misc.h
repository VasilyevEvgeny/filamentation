//
// Created by vasilyev on 22.07.2019.
//

#ifndef FILAMENTATION_FUNCTIONS_H
#define FILAMENTATION_FUNCTIONS_H

#include <complex>
#include <chrono>
#include <iostream>

int generate_random_number(int min, int max);

static struct Constants {
    const double h_bar = 1.054571800e-34;
    const double c = 2.9979245799999954e8;
    const double e = 1.602176620898e-19;
    const double m_e = 9.1093829140e-31;
    const double epsilon_0 = 8.85418781762039e-12;
    const double mu_0 = 4.0 * M_PI * 1e-7;
    const std::complex<double> M_COMPLEX_I = std::complex<double>(0.0, 1.0);
} constants;


using TIME = std::chrono::high_resolution_clock;


#endif //FILAMENTATION_FUNCTIONS_H

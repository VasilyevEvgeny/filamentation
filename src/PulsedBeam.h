//
// Created by vasilyev on 28.06.2019.
//

#ifndef FILAMENTATION_PULSEDBEAM_H
#define FILAMENTATION_PULSEDBEAM_H

#include <iostream>
#include <vector>
#include <complex>
#include <algorithm>

#include "MathConstants.h"

class PulsedBeam {
public:
    explicit PulsedBeam(
            double lmbda,
            size_t M,
            size_t m,
            double r_0,
            size_t n_r,
            double t_0,
            size_t n_t);
    ~PulsedBeam();

    double get_r_max() const;
    void print_field() const;

    void initialize_field();

    void field_to_intensity();

private:
    double lmbda;

    size_t M;
    size_t m;

    double r_0;
    double r_max;
    size_t n_r;
    double dr;
    std::vector<double> rs;

    double t_0;
    double t_max;
    size_t n_t;
    double dt;
    std::vector<double> ts;

    std::vector<std::vector<std::complex<double>>> field;
    std::vector<std::vector<double>> intensity;



};


#endif //FILAMENTATION_PULSEDBEAM_H

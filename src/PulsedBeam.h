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
#include "medium/SiO2.h"
#include "medium/CaF2.h"
#include "medium/LiF.h"

class PulsedBeam {
public:
    explicit PulsedBeam(
            std::string& _medium_name,
            double _lambda_0,
            size_t _M,
            size_t _m,
            double _r_0,
            size_t _n_r,
            double _t_0,
            size_t _n_t);
    ~PulsedBeam();

    double get_r_max() const;
    void print_field() const;

    void initialize_field();

private:
    std::string medium_name;

    const double lambda_0;

    const size_t M;
    const size_t m;

    const double r_0;
    double r_max;
    const size_t n_r;
    double dr;
    std::vector<double> rs;

    const double t_0;
    double t_max;
    const size_t n_t;
    double dt;
    std::vector<double> ts;

    std::vector<std::vector<std::complex<double>>> field;

};


#endif //FILAMENTATION_PULSEDBEAM_H

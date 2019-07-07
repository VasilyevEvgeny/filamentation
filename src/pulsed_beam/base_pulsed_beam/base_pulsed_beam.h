//
// Created by vasilyev on 28.06.2019.
//

#ifndef FILAMENTATION_PULSEDBEAM_H
#define FILAMENTATION_PULSEDBEAM_H

#include <iostream>
#include <vector>
#include <complex>
#include <algorithm>

#include "../../m_constants.h"
#include "../../medium/SiO2.h"
#include "../../medium/CaF2.h"
#include "../../medium/LiF.h"

#include "../../../lib/alglib/src/specialfunctions.h"

template <typename Medium>
class BasePulsedBeam {
public:
    BasePulsedBeam(
            Medium medium,
            double _lambda_0,
            double _r_0,
            size_t _n_r,
            double _t_0,
            size_t _n_t,
            double _p_0_to_p_cr);
    virtual ~BasePulsedBeam();

    double get_r_max() const;
    void print_field() const;

    void initialize_field();

    std::string info;

    Medium medium;

    const double lambda_0;

    size_t M;
    size_t m;

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

    double z_diff;

    double p_0_to_p_cr;
    double p_cr_to_p_g;
    double p_g;
    double p_0;
    double i_0;
    double e_0;

    double calculate_p_g();
    virtual double calculate_p_cr_to_p_g() = 0;
    double calculate_p_0();
    double calculate_i_0();
    double calculate_e_0();

    double max_intensity(double normalize_to);
    double energy(double normalize_to);

    void save_field(int step, std::string& path_to_save);

    std::vector<std::vector<std::complex<double>>> field;

private:

};


#endif //FILAMENTATION_PULSEDBEAM_H

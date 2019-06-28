//
// Created by vasilyev on 28.06.2019.
//

#include "PulsedBeam.h"

PulsedBeam::PulsedBeam(
        double _lmbda,
        size_t _M,
        size_t _m,
        double _r_0,
        size_t _n_r,
        double _t_0,
        size_t _n_t) :
lmbda(_lmbda),
M(_M),
m(_m),
r_0(_r_0),
n_r(_n_r),
t_0(_t_0),
n_t(_n_t){

    // space
    r_max = 10.0 * r_0;
    dr = r_max / n_r;

    rs = std::vector<double>(n_r, 0.0);
    for (size_t k = 0; k < n_r; ++k) {
        rs[k] = k * dr;
    }

    // time
    t_max = 10.0 * t_0;
    dt = t_max / n_t;

    // field
    field = std::vector<std::vector<std::complex<double>>>(n_r, std::vector<std::complex<double>>(n_t, 0.0));
    intensity = std::vector<std::vector<double>>(n_r, std::vector<double>(n_t, 0.0));
}

PulsedBeam::~PulsedBeam() {
    field.erase(field.begin(), field.end());
    intensity.erase(intensity.begin(), intensity.end());
}

void PulsedBeam::initialize_field() {
    for (size_t k = 0; k < n_r; ++k) {
        for (size_t s = 0; s < n_t; ++s) {
            field[k][s] = 0.0;
        }
    }
}

double PulsedBeam::get_r_max() const {
    return r_max;
}

void PulsedBeam::print_field() const {
    for (int k = 0; k < 1024; ++k) {
        for (int s = 0; s < 1024; ++s) {
            std::cout << field[k][s].real() << " -- " << field[k][s].imag() << std::endl;
        }
    }
}
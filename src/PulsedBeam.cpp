//
// Created by vasilyev on 28.06.2019.
//

#include "PulsedBeam.h"

PulsedBeam::PulsedBeam(
        std::string& _medium_name,
        const double _lambda_0,
        const size_t _M,
        const size_t _m,
        const double _r_0,
        const size_t _n_r,
        const double _t_0,
        const size_t _n_t) :
  medium_name(_medium_name)
, lambda_0(_lambda_0)
, M(_M)
, m(_m)
, r_0(_r_0)
, n_r(_n_r)
, t_0(_t_0)
, n_t(_n_t){

    // MathConstants
    MathConstants math_constants;



    // medium
    CaF2 medium1(lambda_0);

    std::cout << medium1.n_0 << std::endl;
    std::cout << medium1.k_0 << std::endl;
    std::cout << medium1.k_1 << std::endl;
    std::cout << medium1.k_2 << std::endl;

    std::cout << "\n";

//    CaF2 medium2(lambda_0,
//                 math_constants.c);
//
//    std::cout << medium2.n_0 << std::endl;
//    std::cout << medium2.k_0 << std::endl;
//    std::cout << medium2.k_1 << std::endl;
//    std::cout << medium2.k_2 << std::endl;
//
//    std::cout << "\n";
//
//    LiF medium3(lambda_0,
//                 math_constants.c);
//
//    std::cout << medium3.n_0 << std::endl;
//    std::cout << medium3.k_0 << std::endl;
//    std::cout << medium3.k_1 << std::endl;
//    std::cout << medium3.k_2 << std::endl;

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

    ts = std::vector<double>(n_t, 0.0);
    for (size_t s = 0; s < n_t; ++s) {
        ts[s] = s * dt;
    }

    // field
    field = std::vector<std::vector<std::complex<double>>>(n_r, std::vector<std::complex<double>>(n_t, 0.0));
}

PulsedBeam::~PulsedBeam() {
    field.erase(field.begin(), field.end());
}

void PulsedBeam::initialize_field() {
    for (size_t k = 0; k < n_r; ++k) {
        for (size_t s = 0; s < n_t; ++s) {
            field[k][s] = pow(rs[k] / r_0, M) * exp(-0.5 * pow(rs[k] / r_0, 2)) * exp(-0.5 * pow(ts[s] / t_0, 2));
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
//
// Created by vasilyev on 28.06.2019.
//

#include <fstream>
#include <sstream>
#include <iomanip>

#include "base_pulsed_beam.h"
#include "../../../lib/alglib/src/specialfunctions.h"

template<typename Medium>
BasePulsedBeam<Medium>::BasePulsedBeam() = default;

template <typename Medium>
BasePulsedBeam<Medium>::BasePulsedBeam(
        Medium _medium,
        double _lambda_0,
        double _r_0,
        size_t _n_r,
        double _t_0,
        size_t _n_t,
        double _p_0_to_p_cr):
  medium(_medium)
, lambda_0(_lambda_0)
, r_0(_r_0)
, n_r(_n_r)
, t_0(_t_0)
, n_t(_n_t)
, p_0_to_p_cr(_p_0_to_p_cr) {

    M = 0;
    m = 0;

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
        ts[s] = s * dt - 0.5 * t_max;
    }

    // z_diff
    z_diff = medium.k_0 * pow(r_0, 2);

    p_cr_to_p_g = 0;
    p_g = calculate_p_g();
    p_0 = 0;
    i_0 = 0;
    e_0 = 0;

    // field
    field = std::vector<std::vector<std::complex<double>>>(n_r, std::vector<std::complex<double>>(n_t, 0.0));
}

template<typename Medium>
BasePulsedBeam<Medium>::~BasePulsedBeam() {
    field.erase(field.begin(), field.end());
}

template class BasePulsedBeam<SiO2>;
template class BasePulsedBeam<CaF2>;
template class BasePulsedBeam<LiF>;




template<typename Medium>
double BasePulsedBeam<Medium>::get_r_max() const {
    return r_max;
}

template<typename Medium>
void BasePulsedBeam<Medium>::print_field() const {
    for (int k = 0; k < 1024; ++k) {
        for (int s = 0; s < 1024; ++s) {
            std::cout << field[k][s].real() << " -- " << field[k][s].imag() << std::endl;
        }
    }
}
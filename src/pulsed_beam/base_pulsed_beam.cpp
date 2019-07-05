//
// Created by vasilyev on 28.06.2019.
//

#include "base_pulsed_beam.h"
#include "../../lib/alglib/src/specialfunctions.h"

template <typename Medium>
BasePulsedBeam<Medium>::BasePulsedBeam(
        Medium _medium,
        const double _lambda_0,
        const double _r_0,
        const size_t _n_r,
        const double _t_0,
        const size_t _n_t,
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
        ts[s] = s * dt;
    }

    // z_diff
    z_diff = medium.k_0 * pow(r_0, 2);

    p_cr_to_p_g = 0;
    p_g = calculate_p_g();
    p_0 = 0;
    i_0 = 0;

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
double BasePulsedBeam<Medium>::max_intensity(double normalized_to) {
    double max_intensity = 0.0;
    for (size_t k = 0; k < n_r; ++k) {
        for (size_t s = 0; s < n_t; ++s) {
            double current_intensity = norm(field[k][s]);
            if (max_intensity < current_intensity) {
                max_intensity = current_intensity;
            }
        }
    }

    return max_intensity * i_0 / normalized_to;

}

template<typename Medium>
void BasePulsedBeam<Medium>::initialize_field() {
    for (size_t k = 0; k < n_r; ++k) {
        for (size_t s = 0; s < n_t; ++s) {
            field[k][s] = pow(rs[k] / r_0, M) * exp(-0.5 * pow(rs[k] / r_0, 2)) * exp(-0.5 * pow(ts[s] / t_0, 2));
        }
    }
}

template<typename Medium>
double BasePulsedBeam<Medium>::calculate_p_g() {
    return 3.77 * pow(lambda_0, 2) / (8 * M_PI * medium.n_0 * medium.n_2);
}

template<typename Medium>
double BasePulsedBeam<Medium>::calculate_p_0() {
    return BasePulsedBeam<Medium>::p_0_to_p_cr * BasePulsedBeam<Medium>::p_cr_to_p_g * BasePulsedBeam<Medium>::p_g;
}

template<typename Medium>
double BasePulsedBeam<Medium>::calculate_i_0() {
    return BasePulsedBeam<Medium>::p_0 / (M_PI * pow(BasePulsedBeam<Medium>::r_0, 2) *
           alglib::gammafunction(BasePulsedBeam<Medium>::M + 1));
}


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
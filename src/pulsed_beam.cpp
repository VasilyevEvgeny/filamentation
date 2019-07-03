//
// Created by vasilyev on 28.06.2019.
//

#include "pulsed_beam.h"

template <typename Medium>
PulsedBeam<Medium>::PulsedBeam(
        Medium _medium,
        const double _lambda_0,
        const size_t _M,
        const size_t _m,
        const double _r_0,
        const size_t _n_r,
        const double _t_0,
        const size_t _n_t):
  medium(_medium)
, lambda_0(_lambda_0)
, M(_M)
, m(_m)
, r_0(_r_0)
, n_r(_n_r)
, t_0(_t_0)
, n_t(_n_t){

    // MathConstants
    // MathConstants math_constants;

    space_distribution = classify_space_distribution();
    time_distribution = "Gaussian";

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

    // field
    field = std::vector<std::vector<std::complex<double>>>(n_r, std::vector<std::complex<double>>(n_t, 0.0));
}

template<typename Medium>
PulsedBeam<Medium>::~PulsedBeam() {
    field.erase(field.begin(), field.end());
}

template class PulsedBeam<SiO2>;
template class PulsedBeam<CaF2>;
template class PulsedBeam<LiF>;

template <typename Medium>
std::string PulsedBeam<Medium>::classify_space_distribution() {
    try {
        if (M == 0 && m == 0) {
            return "Gaussian";
        }
        else if (M > 0 && m == 0) {
            return "ring";
        }
        else if (M > 0 && m > 0) {
            return "vortex";
        }
        else {
            throw std::runtime_error("Wrong combination of M and m!");
        }
    }
    catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

}


template<typename Medium>
void PulsedBeam<Medium>::initialize_field() {
    for (size_t k = 0; k < n_r; ++k) {
        for (size_t s = 0; s < n_t; ++s) {
            field[k][s] = pow(rs[k] / r_0, M) * exp(-0.5 * pow(rs[k] / r_0, 2)) * exp(-0.5 * pow(ts[s] / t_0, 2));
        }
    }
}

template<typename Medium>
double PulsedBeam<Medium>::get_r_max() const {
    return r_max;
}

template<typename Medium>
void PulsedBeam<Medium>::print_field() const {
    for (int k = 0; k < 1024; ++k) {
        for (int s = 0; s < 1024; ++s) {
            std::cout << field[k][s].real() << " -- " << field[k][s].imag() << std::endl;
        }
    }
}
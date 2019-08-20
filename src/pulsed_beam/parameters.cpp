//
// Created by vasilyev on 05.07.2019.
//

#include <cmath>

#include "pulsed_beam/base_pulsed_beam.h"


double BasePulsedBeam::max_intensity(double normalize_to) {
    double max_intensity = 0.0;
    for (size_t k = 0; k < n_r; ++k) {
        for (size_t s = 0; s < n_t; ++s) {
            double current_intensity = norm(field[k][s]);
            if (max_intensity < current_intensity) {
                max_intensity = current_intensity;
            }
        }
    }

    return max_intensity * i_0 / normalize_to;
}

double BasePulsedBeam::calculate_e_0() {
    return p_0 * sqrt(M_PI) * t_0;
}


double BasePulsedBeam::energy(double normalize_to) {
    double sum = 0.0;
    for (size_t k = 0; k < n_r; ++k) {
        for (size_t s = 0; s < n_t; ++s) {
            sum += norm(field[k][s]) * rs[k];
        }
    }

    return sum * i_0 * 2 * M_PI * dr * dt / normalize_to;
}


void BasePulsedBeam::initialize_field() {
    for (size_t k = 0; k < n_r; ++k) {
        for (size_t s = 0; s < n_t; ++s) {
            field[k][s] = pow(rs[k] / r_0, M) * exp(-0.5 * pow(rs[k] / r_0, 2)) * exp(-0.5 * pow(ts[s] / t_0, 2));
        }
    }
}


double BasePulsedBeam::calculate_p_g() {
    return 3.77 * pow(lambda_0, 2) / (8 * M_PI * medium->n_0 * medium->n_2);
}


double BasePulsedBeam::calculate_p_0() {
    return BasePulsedBeam::p_0_to_p_cr * BasePulsedBeam::p_cr_to_p_g * BasePulsedBeam::p_g;
}


double BasePulsedBeam::calculate_i_0() {
    return BasePulsedBeam::p_0 / (M_PI * pow(BasePulsedBeam::r_0, 2) *
                                          alglib::gammafunction(BasePulsedBeam::M + 1));
}

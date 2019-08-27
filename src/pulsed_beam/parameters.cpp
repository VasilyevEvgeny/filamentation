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

    return max_intensity * I_0 / normalize_to;
}

double BasePulsedBeam::calculate_E_0() {
    return P_0 * sqrt(M_PI) * t_0;
}


double BasePulsedBeam::energy(double normalize_to) {
    double sum = 0.0;
    for (size_t k = 0; k < n_r; ++k) {
        for (size_t s = 0; s < n_t; ++s) {
            sum += norm(field[k][s]) * rs[k];
        }
    }

    return sum * I_0 * 2 * M_PI * dr * dt / normalize_to;
}


void BasePulsedBeam::initialize_field() {
    for (size_t k = 0; k < n_r; ++k) {
        for (size_t s = 0; s < n_t; ++s) {
            field[k][s] = pow(rs[k] / r_0, M) * exp(-0.5 * pow(rs[k] / r_0, 2)) * exp(-0.5 * pow(ts[s] / t_0, 2));
        }
    }
}


double BasePulsedBeam::calculate_P_G() {
    return 3.77 * pow(lambda_0, 2) / (8 * M_PI * medium->n_0 * medium->n_2);
}


double BasePulsedBeam::calculate_P_0() {
    return P_0_to_P_cr * P_cr_to_P_G * P_G;
}


double BasePulsedBeam::calculate_I_0() {
    return P_0 / (M_PI * pow(r_0, 2) * alglib::gammafunction(M + 1));
}

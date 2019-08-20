//
// Created by vasilyev on 28.06.2019.
//

#include <iostream>
#include <algorithm>

#include <fstream>
#include <sstream>
#include <iomanip>
#include <memory>

#include "misc/misc.h"
#include "base_pulsed_beam.h"
#include "logger/logger.h"

//template<typename Medium>
BasePulsedBeam::BasePulsedBeam() = default;


//template <typename Medium>
BasePulsedBeam::BasePulsedBeam(
        std::shared_ptr<BaseMedium>& _medium,
        ConfigManager& _config_manager,
        std::shared_ptr<Logger>& _logger)
: medium(_medium)
, lambda_0(_config_manager.lambda_0)
, r_0(_config_manager.r_0)
, n_r(_config_manager.n_r)
, t_0(_config_manager.t_0)
, n_t(_config_manager.n_t)
, p_0_to_p_cr(_config_manager.p_0_to_p_cr)
, logger(_logger) {

    logger->add_propagation_event(std::string("creating pulsed_beam"));

    omega_0 = 2 * M_PI * constants.c / lambda_0;

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

    // frequency
    domega = 2 * M_PI / t_max;
    Omegas = std::vector<double>(n_t, 0.0);
    for (size_t s = 0; s < n_t; ++s) {
        if (s < n_t / 2) {
            Omegas[s] = domega * s;
        }
        else {
            Omegas[s] = domega * (n_t - s);
        }
    }

    // lengths
    z_diff = medium->k_0 * pow(r_0, 2);
    z_disp = pow(t_0, 2) / medium->k_2;

    p_cr_to_p_g = 0;
    p_g = calculate_p_g();
    p_0 = 0;
    i_0 = 0;
    e_0 = 0;

    // field
    field = std::vector<std::vector<std::complex<double>>>(n_r, std::vector<std::complex<double>>(n_t, 0.0));

    // spectrum
    spectrum = std::vector<std::vector<std::complex<double>>>(n_r, std::vector<std::complex<double>>(n_t, 0.0));

    // plasma
    plasma = std::vector<std::vector<double>>(n_r, std::vector<double>(n_t, 0.0));
}





//template<typename Medium>
BasePulsedBeam::~BasePulsedBeam() {
    field.erase(field.begin(), field.end());
    spectrum.erase(spectrum.begin(), spectrum.end());
    plasma.erase(plasma.begin(), plasma.end());
}

//template class BasePulsedBeam<SiO2>;
//template class BasePulsedBeam<CaF2>;
//template class BasePulsedBeam<LiF>;
//
//template class BasePulsedBeam<BaseMedium>;


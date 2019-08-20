//
// Created by vasilyev on 02.07.2019.
//

#include <cmath>

#include "SiO2.h"

SiO2::SiO2() = default;

SiO2::SiO2(ConfigManager& _config_manager, std::shared_ptr<Logger>& _logger)
: BaseMedium(_config_manager, _logger) {

    info = "SiO$_2$";
    name = "SiO2";

    lambda_1 = 0.0684043000e-6;
    lambda_2 = 0.1162414000e-6;
    lambda_3 = 9.8961610000e-6;

    BaseMedium::initialize_omegas();

    C_1 = 0.6961663000;
    C_2 = 0.4079426000;
    C_3 = 0.8974794000;

    BaseMedium::initialize_dispersion_parameters();
    SiO2::initialize_kerr_parameters();
    SiO2::initialize_ionization_parameters();

    delta = 0;

    BaseMedium::initialize_ionization();
}

SiO2::~SiO2() = default;

void SiO2::initialize_kerr_parameters() {
    n_2 = 3.40e-20;
    g = 0.18;
    Omega_R = 1e13;
    tau_k = 32e-15;
    conv_kernel_const = calculate_conv_kernel_const();
    conv_window = 80e-15;
}

void SiO2::initialize_ionization_parameters() {
    N_0 = 2.66e28;
    U_i_in_eV = 9;
    U_i = U_i_in_eV * constants.e;
    ItoA_const = calculate_ItoA_const();
    v_ei = 1e14;
    v_i_const = calculate_v_i_const();
    beta = 6.7e12;
    K = calculate_K();
}



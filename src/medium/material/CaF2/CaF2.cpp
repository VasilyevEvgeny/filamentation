//
// Created by vasilyev on 02.07.2019.
//

#include "CaF2.h"

CaF2::CaF2() = default;

CaF2::CaF2(ConfigManager& _config_manager, std::shared_ptr<Logger>& _logger)
: BaseMedium(_config_manager, _logger) {

    name = "CaF2";
    formula = "CaF$_2$";

    lambda_1 = 0.0502636050e-6;
    lambda_2 = 0.1003909000e-6;
    lambda_3 = 34.649040000e-6;

    BaseMedium::initialize_omegas();

    C_1 = 0.5675888000;
    C_2 = 0.4710914000;
    C_3 = 3.8484723000;

    BaseMedium::initialize_dispersion_parameters();
    CaF2::initialize_kerr_parameters();
    CaF2::initialize_ionization_parameters();

    delta = 0;

    if (!config_manager.active_nonlinear_terms.empty()) {
        BaseMedium::initialize_ionization();
    }
}

CaF2::~CaF2() = default;

void CaF2::initialize_kerr_parameters() {
    n_2 = 1.92e-20;
    g = 0.18;
    Omega_R = 1e13;
    tau_k = 32e-15;
    conv_kernel_const = calculate_conv_kernel_const();
    conv_window = 80e-15;
}

void CaF2::initialize_ionization_parameters() {
    N_0 = 2.46e28;
    U_i_in_eV = 10;
    U_i = U_i_in_eV * constants.e;
    ItoA_const = calculate_ItoA_const();
    v_ei = 1e14;
    v_i_const = calculate_v_i_const();
    beta = 6.7e12;
    K = calculate_K();
}

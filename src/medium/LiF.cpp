//
// Created by vasilyev on 02.07.2019.
//

#include "LiF.h"


LiF::LiF(double _lambda_0) : BaseMedium(_lambda_0) {

    info = "LiF";

    lambda_1 = 0.0737600000e-6;
    lambda_2 = 32.790000000e-6;
    lambda_3 = 1e-10;

    BaseMedium::initialize_omegas();

    C_1 = 0.9254900000;
    C_2 = 6.9674700000;
    C_3 = 0.0000000000;

    BaseMedium::initialize_dispersion_parameters();
    LiF::initialize_kerr_parameters();
    LiF::initialize_ionization_parameters();

    delta = 0;

}

LiF::~LiF() = default;

void LiF::initialize_kerr_parameters() {
    n_2 = 1.00e-20;
    g = 0.18;
    Omega_R = 1e13;
    tau_k = 32e-15;
    conv_kernel_const = calculate_conv_kernel_const();
    conv_window = 80e-15;
}

void LiF::initialize_ionization_parameters() {
    N_0 = 6.10e28;
    U_i_in_eV = 13;
    U_i = U_i_in_eV * math_constants.e;
    ItoA_const = calculate_ItoA_const();
    v_ei = 1e14;
    v_i_const = calculate_v_i_const();
    beta = 6.7e12;
    K = calculate_K();
}

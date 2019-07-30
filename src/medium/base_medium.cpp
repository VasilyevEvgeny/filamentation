//
// Created by vasilyev on 01.07.2019.
//

#include <cmath>

#include "medium/base_medium.h"


BaseMedium::BaseMedium() {

    lambda_0 = 0;
    omega_0 = 0;
    c = 0;

    // dispersion parameters
    lambda_1 = 0;
    lambda_2 = 0;
    lambda_3 = 0;

    omega_1 = 0;
    omega_2 = 0;
    omega_3 = 0;

    C_1 = 0;
    C_2 = 0;
    C_3 = 0;

    n_0 = 0;
    k_0 = 0;
    k_1 = 0;
    k_2 = 0;


    // kerr parameters
    n_2 = 0;
    g = 0;
    Omega_R = 0;
    tau_k = 0;
    conv_kernel_const = 0;
    conv_window = 0;


    // ionization_parameters
    N_0 = 0;
    U_i_in_eV = 0;
    U_i = 0;
    ItoA_const = 0;
    v_ei = 0;
    v_i_const = 0;
    beta = 0;
    K = 0;

    delta = 0;
}

BaseMedium::BaseMedium(double _lambda_0)
: lambda_0(_lambda_0) {

    // light speed
    c = math_constants.c;

    info = "";

    // omega_0
    omega_0 = 2 * M_PI * c / lambda_0;

    // dispersion parameters
    lambda_1 = 0;
    lambda_2 = 0;
    lambda_3 = 0;

    omega_1 = 0;
    omega_2 = 0;
    omega_3 = 0;

    C_1 = 0;
    C_2 = 0;
    C_3 = 0;

    n_0 = 0;
    k_0 = 0;
    k_1 = 0;
    k_2 = 0;


    // kerr parameters
    n_2 = 0;
    g = 0;
    Omega_R = 0;
    tau_k = 0;
    conv_kernel_const = 0;
    conv_window = 0;


    // ionization_parameters
    N_0 = 0;
    U_i_in_eV = 0;
    U_i = 0;
    ItoA_const = 0;
    v_ei = 0;
    v_i_const = 0;
    beta = 0;
    K = 0;

    delta = 0;





}

BaseMedium::~BaseMedium() = default;

void BaseMedium::initialize_omegas() {
    omega_1 = 2. * M_PI * c / lambda_1;
    omega_2 = 2. * M_PI * c / lambda_2;
    omega_3 = 2. * M_PI * c / lambda_3;
}

double BaseMedium::calculate_n(double omega) {
    /*
    Linear refractive index is calculated from the Sellmeier formula
    (//: https://refractiveindex.info/?shelf=glass&book=fused_silica&page=Malitson)

    :param omega: beam frequency, \omega = 2 \pi c / \lambda
    :param C_1: parameter in Sellmeier formula
    :param C_2: parameter in Sellmeier formula
    :param C_3: parameter in Sellmeier formula
    :param omega_1: resonance frequency
    :param omega_2: resonance frequency
    :param omega_3: resonance frequency
    :return:
    */
    return sqrt(1 + \
                C_1 / (1 - pow((omega / omega_1), 2)) + \
                C_2 / (1 - pow((omega / omega_2), 2)) + \
                C_3 / (1 - pow((omega / omega_3), 2)));
}

double BaseMedium::calculate_k(double omega) {
    /*
    Calculates wave vector
            k_0 = \omega * n(\omega) / c
    */

    return omega / c * calculate_n(omega);
}

double BaseMedium::calculate_k_1(double omega) {
    /*
    Calculates k_1 = dk / dw |_w=\omega using the analytical expression of the first derivative
    of the Sellmeier formula
    */

    return omega * (C_1 * omega / (pow(omega_1, 2) * pow(-pow(omega, 2) / pow(omega_1, 2) + 1, 2)) +
                    C_2 * omega / (pow(omega_2, 2) * pow(-pow(omega, 2) / pow(omega_2, 2) + 1, 2)) +
                    C_3 * omega / (pow(omega_3, 2) * pow(-pow(omega, 2) / pow(omega_3, 2) + 1, 2))) /
                   (c * sqrt(C_1 / (-pow(omega, 2) / pow(omega_1, 2) + 1) +
                             C_2 / (-pow(omega, 2) / pow(omega_2, 2) + 1) +
                             C_3 / (-pow(omega, 2) / pow(omega_3, 2) + 1) + 1)) +
           sqrt(C_1 / (-pow(omega, 2) / pow(omega_1, 2) + 1) +
                C_2 / (-pow(omega, 2) / pow(omega_2, 2) + 1) +
                C_3 / (-pow(omega, 2) / pow(omega_3, 2) + 1) + 1) / c;
}

double BaseMedium::calculate_k_2(double omega) {
    /*
    Calculates
    k_2 = d ^ 2k / dw ^ 2 | _w =\omega using the analytical expression of the second derivative of the Sellmeier formula
    */

    return omega * (-C_1 * omega / (pow(omega_1, 2) * pow(-pow(omega, 2) / pow(omega_1, 2) + 1, 2))
                    -C_2 * omega / (pow(omega_2, 2) * pow(-pow(omega, 2) / pow(omega_2, 2) + 1, 2))
                    -C_3 * omega / (pow(omega_3, 2) * pow(-pow(omega, 2) / pow(omega_3, 2) + 1, 2))) *
           (C_1 * omega / (pow(omega_1, 2) * pow(-pow(omega, 2) / pow(omega_1, 2) + 1, 2)) +
            C_2 * omega / (pow(omega_2, 2) * pow(-pow(omega, 2) / pow(omega_2, 2) + 1, 2)) +
            C_3 * omega / (pow(omega_3, 2) * pow(-pow(omega, 2) / pow(omega_3, 2) + 1, 2))) /
           (c * pow(C_1 / (-pow(omega, 2) / pow(omega_1, 2) + 1) +
                    C_2 / (-pow(omega, 2) / pow(omega_2, 2) + 1) +
                    C_3 / (-pow(omega, 2) / pow(omega_3, 2) + 1) + 1, 1.5)) +
           omega * (4 * C_1 * pow(omega, 2) / (pow(omega_1, 4) * pow(-pow(omega, 2) / pow(omega_1, 2) + 1, 3)) +
                    C_1 / (pow(omega_1, 2) * pow(-pow(omega, 2) / pow(omega_1, 2) + 1, 2)) +
                    4 * C_2 * pow(omega, 2) / (pow(omega_2, 4) * pow(-pow(omega, 2) / pow(omega_2, 2) + 1, 3)) +
                    C_2 / (pow(omega_2, 2) * pow(-pow(omega, 2) / pow(omega_2, 2) + 1, 2)) +
                    4 * C_3 * pow(omega, 2) / (pow(omega_3, 4) * pow(-pow(omega, 2) / pow(omega_3, 2) + 1, 3)) +
                    C_3 / (pow(omega_3, 2) * pow(-pow(omega, 2) / pow(omega_3, 2) + 1, 2))) /
           (c * sqrt(C_1 / (-pow(omega, 2) / pow(omega_1, 2) + 1) +
                     C_2 /(-pow(omega, 2) / pow(omega_2, 2) + 1) +
                     C_3 / (-pow(omega, 2) / pow(omega_3, 2) + 1) + 1)) +
           2 * (C_1 * omega / (pow(omega_1, 2) * pow(-pow(omega, 2) / pow(omega_1, 2) + 1, 2)) +
                C_2 * omega / (pow(omega_2, 2) * pow(-pow(omega, 2) / pow(omega_2, 2) + 1, 2)) +
                C_3 * omega / (pow(omega_3, 2) * pow(-pow(omega, 2) / pow(omega_3, 2) + 1, 2))) /
           (c * sqrt(C_1 / (-pow(omega, 2) / pow(omega_1, 2) + 1) +
                     C_2 / (-pow(omega, 2) / pow(omega_2, 2) + 1) +
                     C_3 / (-pow(omega, 2) / pow(omega_3, 2) + 1) + 1));
}

void BaseMedium::initialize_dispersion_parameters() {
    /*
    Calculates all dispersion parameters in class
    */

    n_0 = calculate_n(omega_0);
    k_0 = calculate_k(omega_0);
    k_1 = calculate_k_1(omega_0);
    k_2 = calculate_k_2(omega_0);
}

double BaseMedium::calculate_conv_kernel_const() {
    return (1 + pow(Omega_R * tau_k, 2)) / (Omega_R * pow(tau_k, 2));
}

double BaseMedium::calculate_ItoA_const() {
    return 2.0 / (c * n_0 * math_constants.epsilon_0);
}

double BaseMedium::calculate_v_i_const() {
    return pow(math_constants.e, 2) * v_ei / (U_i * 2.0 * math_constants.m_e * (pow(omega_0, 2) + pow(v_ei, 2))) * ItoA_const;
}

int BaseMedium::calculate_K() {
    return (int)(U_i / (math_constants.h_bar * omega_0) + 1);
}


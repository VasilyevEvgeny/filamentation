//
// Created by vasilyev on 28.07.2019.
//

#include <iostream>

#include "base_keldysh.h"

#include "specialfunctions.h"


BaseKeldysh::BaseKeldysh()
: omega_0(0)
, U_i(0)
, N_0(0)
, n_0(0)
, kappa(0)
, m_efficient(0) {}


BaseKeldysh::BaseKeldysh(
        double _omega_0,
        double _U_i,
        double _N_0,
        double _n_0)
: omega_0(_omega_0)
, U_i(_U_i)
, N_0(_N_0)
, n_0(_n_0){

    math_constants = MathConstants();

    kappa = 0.64;
    m_efficient = kappa * math_constants.m_e;

}

BaseKeldysh::~BaseKeldysh() = default;



double BaseKeldysh::calculate_E(double i) {
    return sqrt(sqrt(math_constants.mu_0 / math_constants.epsilon_0) * 2.0 * i / n_0);
}

double BaseKeldysh::calculate_gamma(double E) {
    return omega_0 * sqrt(m_efficient * U_i) / (math_constants.e * E);
}

double BaseKeldysh::calculate_Gamma(double gamma) {
    return pow(gamma, 2) / (1 + pow(gamma, 2));
}

double BaseKeldysh::calculate_Xi(double gamma) {
    return 1.0 / (1.0 + pow(gamma, 2));
}

double BaseKeldysh::calculate_alpha(double Gamma, double Xi) {
    return M_PI * (alglib::ellipticintegralk(Gamma) - alglib::ellipticintegrale(Gamma)) / alglib::ellipticintegrale(Xi);
}

double BaseKeldysh::calculate_beta(double Xi) {
    return pow(M_PI, 2) / (4.0 * alglib::ellipticintegralk(Xi) * alglib::ellipticintegrale(Xi));
}

double BaseKeldysh::calculate_x(double Gamma, double Xi) {
    return 2.0 * U_i * alglib::ellipticintegrale(Xi) / (M_PI * math_constants.h_bar * omega_0 * sqrt(Gamma));
}

double BaseKeldysh::calculate_v(double x_plus_1, double x) {
    return x_plus_1 - x;
}

double BaseKeldysh::calculate_Q(double alpha, double beta, double v, double Xi) {
    double sum = 0.0;
    for (size_t n = 0; n < 100; ++n) {
        sum += exp(-alpha * n) * alglib::dawsonintegral(sqrt(beta * (n + 2 * v)));
//        std::cout << "sum = " << sum << std::endl;
    }

    return sqrt(M_PI / (2.0 * alglib::ellipticintegralk(Xi))) * sum;
}

double BaseKeldysh::calculate_W(double x_plus_1, double alpha, double Gamma, double Q) {
    return (2.0 * omega_0 / (9.0 * M_PI)) * pow(m_efficient * omega_0 / (math_constants.h_bar * sqrt(Gamma)), 1.5) *
           Q * exp(-alpha * x_plus_1);
}

double BaseKeldysh::R(double i) {

    double E = calculate_E(i);
    double gamma = calculate_gamma(E);
    double Gamma = calculate_Gamma(gamma);
    double Xi = calculate_Xi(gamma);
    double alpha = calculate_alpha(Gamma, Xi);
    double beta = calculate_beta(Xi);
    double x = calculate_x(Gamma, Xi);
    double x_plus_1 = calculate_x_plus_1(x);
    double v = calculate_v(x_plus_1, x);
    double Q = calculate_Q(alpha, beta, v, Xi);
    double W = calculate_W(x_plus_1, alpha, Gamma, Q);

//    std::cout << E << std::endl;
//    std::cout << gamma << std::endl;
//    std::cout << Gamma << std::endl;
//    std::cout << Xi << std::endl;
//    std::cout << alpha << std::endl;
//    std::cout << beta << std::endl;
//    std::cout << x << std::endl;
//    std::cout << x_plus_1 << std::endl;
//    std::cout << v << std::endl;
//    std::cout << Q << std::endl;
//    std::cout << W << std::endl;

    return W / N_0;
}
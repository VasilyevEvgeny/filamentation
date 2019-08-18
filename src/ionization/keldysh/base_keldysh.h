//
// Created by vasilyev on 28.07.2019.
//

#ifndef FILAMENTATION_BASE_KELDYSH_IONIZATION_H
#define FILAMENTATION_BASE_KELDYSH_IONIZATION_H

#include "../base_ionization.h"
#include "m_constants.h"

class BaseKeldysh : public BaseIonization {
public:
    BaseKeldysh();
    explicit BaseKeldysh(double _omega_0,
                         double _U_i,
                         double _N_0,
                         double _n_0);

    ~BaseKeldysh() override;

    double omega_0;
    double U_i;
    double N_0;
    double n_0;

    MathConstants math_constants;

    double kappa;
    double m_efficient;


    double calculate_E(double i);
    double calculate_gamma(double E);
    double calculate_Gamma(double gamma);
    double calculate_Xi(double gamma);
    double calculate_alpha(double Gamma, double Xi);
    double calculate_beta(double Xi);
    double calculate_x(double Gamma, double Xi);
    virtual double calculate_x_plus_1(double x) = 0;
    double calculate_v(double x_plus_1, double x);
    double calculate_Q(double alpha, double beta, double v, double Xi);
    double calculate_W(double x_plus_1, double alpha, double Gamma, double Q);


    double calculate_R(double i) override;
};


#endif //FILAMENTATION_BASE_KELDYSH_IONIZATION_H

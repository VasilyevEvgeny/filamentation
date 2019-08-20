//
// Created by vasilyev on 01.07.2019.
//

#ifndef FILAMENTATION_MEDIUM_H
#define FILAMENTATION_MEDIUM_H

#include <iostream>
#include <memory>

#include "misc_functions.h"

#include "logger/logger.h"
#include "manager/config_manager/config_manager.h"
#include "medium/ionization/keldysh/original_keldysh.h"
#include "medium/ionization/keldysh/smoothed_keldysh.h"

class BaseMedium {

public:
    BaseMedium();
    explicit BaseMedium(ConfigManager& _config_manager, std::shared_ptr<Logger>& _logger);
    virtual ~BaseMedium() = 0;

    std::shared_ptr<Logger> logger;

    ConfigManager config_manager;


    std::shared_ptr<BaseIonization> ionization;

    std::string info;
    std::string name;

    // central wavelength
    double lambda_0;
    double omega_0;

    // light speed
    double c;

    // dispersion parameters
    double lambda_1;
    double lambda_2;
    double lambda_3;

    double omega_1;
    double omega_2;
    double omega_3;

    double C_1;
    double C_2;
    double C_3;

    double n_0;
    double k_0;
    double k_1;
    double k_2;


    // kerr parameters
    double n_2;
    double g;
    double Omega_R;
    double tau_k;
    double conv_kernel_const;
    double conv_window;


    // ionization_parameters
    double N_0;
    double U_i_in_eV;
    double U_i;
    double ItoA_const;
    double v_ei;
    double v_i_const;
    double beta;
    int K;

    //extinction
    double delta;



    void initialize_omegas();
    void initialize_dispersion_parameters();
    virtual void initialize_kerr_parameters() = 0;
    virtual void initialize_ionization_parameters() = 0;

    double calculate_n(double omega);
    double calculate_k(double omega);
    double calculate_k_1(double omega);
    double calculate_k_2(double omega);

    double calculate_conv_kernel_const();
    double calculate_ItoA_const();
    double calculate_v_i_const();
    int calculate_K();

    void initialize_ionization();

private:

};


#endif //FILAMENTATION_MEDIUM_H

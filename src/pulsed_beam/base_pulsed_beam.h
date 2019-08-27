//
// Created by vasilyev on 28.06.2019.
//

#ifndef FILAMENTATION_PULSEDBEAM_H
#define FILAMENTATION_PULSEDBEAM_H

#include <vector>
#include <complex>
#include <memory>

#include "medium/material/SiO2/SiO2.h"
#include "medium/material/CaF2/CaF2.h"
#include "medium/material/LiF/LiF.h"
#include "specialfunctions.h"
#include "manager/config_manager/config_manager.h"


class BasePulsedBeam {
public:
    BasePulsedBeam();
    explicit BasePulsedBeam(std::shared_ptr<BaseMedium>& _medium,
                            ConfigManager& _config_manager,
                            std::shared_ptr<Logger>& _logger);
    virtual ~BasePulsedBeam();

    void initialize_field();

    std::string info;

    std::shared_ptr<BaseMedium> medium;
    std::shared_ptr<Logger> logger;

    double lambda_0;
    double omega_0;

    size_t M;
    size_t m;

    double r_0;
    double r_max;
    size_t n_r;
    double dr;
    std::vector<double> rs;

    double t_0;
    double t_max;
    size_t n_t;
    double dt;
    std::vector<double> ts;
    double domega;
    std::vector<double> Omegas;

    double z_diff;
    double z_disp;

    double P_0_to_P_cr;
    double P_cr_to_P_G;
    double P_G;
    double P_0;
    double I_0;
    double E_0;

    double calculate_P_G();
    virtual double calculate_P_cr_to_P_G() = 0;
    double calculate_P_0();
    double calculate_I_0();
    double calculate_E_0();

    double max_intensity(double normalize_to);
    double energy(double normalize_to);

    std::vector<std::vector<std::complex<double>>> field;
    std::vector<std::vector<std::complex<double>>> spectrum;

    std::vector<std::vector<double>> plasma;

    void update();

private:

};


#endif //FILAMENTATION_PULSEDBEAM_H

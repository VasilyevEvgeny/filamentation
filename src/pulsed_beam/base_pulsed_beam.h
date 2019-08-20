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


//template <typename Medium>
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

    double p_0_to_p_cr;
    double p_cr_to_p_g;
    double p_g;
    double p_0;
    double i_0;
    double e_0;

    double calculate_p_g();
    virtual double calculate_p_cr_to_p_g() = 0;
    double calculate_p_0();
    double calculate_i_0();
    double calculate_e_0();

    double max_intensity(double normalize_to);
    double energy(double normalize_to);

    std::vector<std::vector<std::complex<double>>> field;
    std::vector<std::vector<std::complex<double>>> spectrum;

    std::vector<std::vector<double>> plasma;

private:

};




#endif //FILAMENTATION_PULSEDBEAM_H

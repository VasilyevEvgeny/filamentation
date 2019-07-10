//
// Created by vasilyev on 05.07.2019.
//

#include <fstream>

#include "logger.h"


template<template<typename, typename...> class PulsedBeam, typename Medium>
void Logger<PulsedBeam<Medium>>::add_to_yml_file_data(std::string& yml_file_data, std::string& str, std::vector<std::string>& params) {
    char buffer [10000];
    if (params.size() == 1) {
        sprintf(buffer, str.c_str(), params[0].c_str());
    }

    yml_file_data += std::string(buffer);
}

template<template<typename, typename...> class PulsedBeam, typename Medium>
void Logger<PulsedBeam<Medium>>::add_to_yml_file_data(std::string& yml_file_data, std::string& str, std::vector<double>& params) {
    char buffer [10000];
    if (params.size() == 6) {
        sprintf(buffer, str.c_str(), params[0], params[1], params[2], params[3], params[4], params[5]);
    }
    else if (params.size() == 15) {
        sprintf(buffer, str.c_str(), params[0], params[1], params[2], params[3], params[4], params[5], params[6],
                params[7], params[8], params[9], params[10], params[11], params[12], params[13], params[14]);
    }
    else if (params.size() == 20) {
        sprintf(buffer, str.c_str(), params[0], params[1], params[2], params[3], params[4], params[5], params[6],
                params[7], params[8], params[9], params[10], params[11], params[12], params[13], params[14],
                params[15], params[16], params[17], params[18], params[19]);
    }


    yml_file_data += std::string(buffer);
}

template<template<typename, typename...> class PulsedBeam, typename Medium>
void Logger<PulsedBeam<Medium>>::save_initial_parameters_to_yml() {

    std::string yml_file_data;

    std::string yml_file_name = "parameters";
    std::string path = manager.current_results_dir;
    std::string yml_file_path = path + "/" + yml_file_name + ".yml";

    /*
     * Sellmeyer
     */

    std::string data_1 = R"(
sellmeyer:
    C_1: %g
    C_2: %g
    C_3: %g
    lambda_1: %g
    lambda_2: %g
    lambda_3: %g
)";
    std::vector<double> data_1_params = {pulsed_beam.medium.C_1,
                                         pulsed_beam.medium.C_2,
                                         pulsed_beam.medium.C_3,
                                         pulsed_beam.medium.lambda_1,
                                         pulsed_beam.medium.lambda_2,
                                         pulsed_beam.medium.lambda_3};

    Logger::add_to_yml_file_data(yml_file_data, data_1, data_1_params);


    std::string data_2 = R"(
medium:
    material: %s)";
    std::vector<std::string> data_2_params = {pulsed_beam.medium.info};
    Logger::add_to_yml_file_data(yml_file_data, data_2, data_2_params);

    std::string data_3 = R"(
    n_0: %g
    k_0: %g
    k_1: %g
    k_2: %g
    n_2: %g
    g: %g
    Omega_R: %g
    tau_k: %g
    Delta_t: %g
    N_0: %g
    v_ei: %g
    beta: %g
    U_i: %g
    K: %g
    delta: %g
)";

    std::vector<double> data_3_params = {pulsed_beam.medium.n_0,
                                         pulsed_beam.medium.k_0,
                                         pulsed_beam.medium.k_1,
                                         pulsed_beam.medium.k_2,
                                         pulsed_beam.medium.n_2,
                                         pulsed_beam.medium.g,
                                         pulsed_beam.medium.Omega_R,
                                         pulsed_beam.medium.tau_k,
                                         pulsed_beam.medium.conv_window,
                                         pulsed_beam.medium.N_0,
                                         pulsed_beam.medium.v_ei,
                                         pulsed_beam.medium.beta,
                                         pulsed_beam.medium.U_i_in_eV,
                                         (double) pulsed_beam.medium.K,
                                         pulsed_beam.medium.delta
    };

    Logger::add_to_yml_file_data(yml_file_data, data_3, data_3_params);


    std::string data_4 = R"(
pulsed_beam:
    space_distribution : %s)";
    std::vector<std::string> data_4_params = {pulsed_beam.info};
    Logger::add_to_yml_file_data(yml_file_data, data_4, data_4_params);


    std::string data_5 = R"(
    M: %.0f
    m: %.0f
    r_0: %g
    lambda_0: %g
    z_diff: %g
    p_0_to_p_cr: %g
    p_cr_to_p_g: %g
    p_g: %g
    p_0: %g
    i_max_to_i_0: %g
    i_0: %g,
    e_0: %g

grid:
    r_max: %g,
    n_r: %.0f,
    h_r: %g,
    t_max: %g
    n_t: %.0f,
    h_t: %g

track:
    n_z: %0.f,
    h_z_0: %g)";
    std::vector<double> data_5_params = {(double)pulsed_beam.M,
                                         (double)pulsed_beam.m,
                                         pulsed_beam.r_0,
                                         pulsed_beam.lambda_0,
                                         pulsed_beam.z_diff,
                                         pulsed_beam.p_0_to_p_cr,
                                         pulsed_beam.p_cr_to_p_g,
                                         pulsed_beam.p_g,
                                         pulsed_beam.p_0,
                                         pulsed_beam.max_intensity(pulsed_beam.i_0),
                                         pulsed_beam.i_0,
                                         pulsed_beam.e_0,
                                         pulsed_beam.r_max,
                                         (double)pulsed_beam.n_r,
                                         pulsed_beam.dr,
                                         pulsed_beam.t_max,
                                         (double)pulsed_beam.n_t,
                                         pulsed_beam.dt,
                                         track_info["n_z"],
                                         track_info["dz"]};
    Logger::add_to_yml_file_data(yml_file_data, data_5, data_5_params);



    std::ofstream f(yml_file_path);
    f << yml_file_data;
    f.close();

}


template class Logger<Gauss<SiO2>>;
template class Logger<Gauss<CaF2>>;
template class Logger<Gauss<LiF>>;
template class Logger<Ring<SiO2>>;
template class Logger<Ring<CaF2>>;
template class Logger<Ring<LiF>>;
template class Logger<Vortex<SiO2>>;
template class Logger<Vortex<CaF2>>;
template class Logger<Vortex<LiF>>;
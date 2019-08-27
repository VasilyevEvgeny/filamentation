//
// Created by vasilyev on 05.07.2019.
//

#include <fstream>

#include "saver/saver.h"


void Saver::add_to_yml_file_data(std::string& yml_file_data, std::string& str, std::vector<std::string>& params) const {
    char buffer [10000];
    if (params.size() == 1) {
        sprintf(buffer, str.c_str(), params[0].c_str());
    }
    if (params.size() == 3) {
        sprintf(buffer, str.c_str(), params[0].c_str(), params[1].c_str(), params[2].c_str());
    }

    yml_file_data += std::string(buffer);
}


void Saver::add_to_yml_file_data(std::string& yml_file_data, std::string& str, std::vector<double>& params) const {
    char buffer [10000];
    if (params.size() == 6) {
        sprintf(buffer, str.c_str(), params[0], params[1], params[2], params[3], params[4], params[5]);
    }
    else if (params.size() == 15) {
        sprintf(buffer, str.c_str(), params[0], params[1], params[2], params[3], params[4], params[5], params[6],
                params[7], params[8], params[9], params[10], params[11], params[12], params[13], params[14]);
    }
    else if (params.size() == 23) {
        sprintf(buffer, str.c_str(), params[0], params[1], params[2], params[3], params[4], params[5], params[6],
                params[7], params[8], params[9], params[10], params[11], params[12], params[13], params[14],
                params[15], params[16], params[17], params[18], params[19], params[20], params[21], params[22]);
    }


    yml_file_data += std::string(buffer);
}


void Saver::save_initial_parameters_to_yml() {

    logger->add_propagation_event(std::string("....saving initial parameters to yml"));

    std::string yml_file_data;

    std::string yml_file_name = "parameters";
    std::string path = dir_manager.current_results_dir;
    std::string yml_file_path = path + "/" + yml_file_name + ".yml";

    /*
     * Sellmeyer
     */

    std::string data_1 = R"(
sellmeyer:
    C_1: %e
    C_2: %e
    C_3: %e
    lambda_1: %e
    lambda_2: %e
    lambda_3: %e
)";
    std::vector<double> data_1_params = {pulsed_beam->medium->C_1,
                                         pulsed_beam->medium->C_2,
                                         pulsed_beam->medium->C_3,
                                         pulsed_beam->medium->lambda_1,
                                         pulsed_beam->medium->lambda_2,
                                         pulsed_beam->medium->lambda_3};

    Saver::add_to_yml_file_data(yml_file_data, data_1, data_1_params);


    std::string data_2 = R"(
medium:
    name: %s
    formula: %s
    ionization: %s)";
    std::vector<std::string> data_2_params = {pulsed_beam->medium->name,
                                              pulsed_beam->medium->formula,
                                              config_manager.ionization};
    Saver::add_to_yml_file_data(yml_file_data, data_2, data_2_params);

    std::string data_3 = R"(
    n_0: %e
    k_0: %e
    k_1: %e
    k_2: %e
    n_2: %e
    g: %e
    Omega_R: %e
    tau_k: %e
    Delta_t: %e
    N_0: %e
    v_ei: %e
    beta: %e
    U_i_in_eV: %e
    K: %e
    delta: %e
)";

    std::vector<double> data_3_params = {pulsed_beam->medium->n_0,
                                         pulsed_beam->medium->k_0,
                                         pulsed_beam->medium->k_1,
                                         pulsed_beam->medium->k_2,
                                         pulsed_beam->medium->n_2,
                                         pulsed_beam->medium->g,
                                         pulsed_beam->medium->Omega_R,
                                         pulsed_beam->medium->tau_k,
                                         pulsed_beam->medium->conv_window,
                                         pulsed_beam->medium->N_0,
                                         pulsed_beam->medium->v_ei,
                                         pulsed_beam->medium->beta,
                                         pulsed_beam->medium->U_i_in_eV,
                                         (double) pulsed_beam->medium->K,
                                         pulsed_beam->medium->delta
    };

    Saver::add_to_yml_file_data(yml_file_data, data_3, data_3_params);


    std::string data_4 = R"(
pulsed_beam:
    space_distribution : %s)";
    std::vector<std::string> data_4_params = {pulsed_beam->info};
    Saver::add_to_yml_file_data(yml_file_data, data_4, data_4_params);


    std::string data_5 = R"(
    M: %.0f
    m: %.0f
    r_0: %e
    t_0: %e
    lambda_0: %e
    z_diff: %e
    z_disp: %e
    P_0_to_P_cr: %e
    P_cr_to_P_G: %e
    P_G: %e
    P_0: %e
    I_max_to_I_0: %e
    I_0: %e
    E_0: %e

grid:
    r_max: %e
    n_r: %.0f
    dr: %e
    t_max: %e
    n_t: %.0f
    dt: %g

track:
    n_z: %0.f
    dz_0: %e
    max_intensity_to_stop: %e)";
    std::vector<double> data_5_params = {(double)pulsed_beam->M,
                                         (double)pulsed_beam->m,
                                         pulsed_beam->r_0,
                                         pulsed_beam->t_0,
                                         pulsed_beam->lambda_0,
                                         pulsed_beam->z_diff,
                                         pulsed_beam->z_disp,
                                         pulsed_beam->P_0_to_P_cr,
                                         pulsed_beam->P_cr_to_P_G,
                                         pulsed_beam->P_G,
                                         pulsed_beam->P_0,
                                         pulsed_beam->max_intensity(pulsed_beam->I_0),
                                         pulsed_beam->I_0,
                                         pulsed_beam->E_0,
                                         pulsed_beam->r_max,
                                         (double)pulsed_beam->n_r,
                                         pulsed_beam->dr,
                                         pulsed_beam->t_max,
                                         (double)pulsed_beam->n_t,
                                         pulsed_beam->dt,
                                         (double)config_manager.n_z,
                                         config_manager.dz_0,
                                         config_manager.max_intensity_to_stop};
    Saver::add_to_yml_file_data(yml_file_data, data_5, data_5_params);



    std::ofstream f(yml_file_path);
    f << yml_file_data;
    f.close();

}

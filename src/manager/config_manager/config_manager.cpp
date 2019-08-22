//
// Created by vasilyev on 07.08.2019.
//

#include "config_manager.h"

#include <sstream>
#include <fstream>
#include <omp.h>
#include <algorithm>



ConfigManager::ConfigManager() = default;

ConfigManager::ConfigManager(const std::string& _path_to_config)
: path_to_config(_path_to_config) {

    parse_config();
    validate_config();
}

ConfigManager::~ConfigManager() = default;


void ConfigManager::parse_config() {

    std::ifstream f(path_to_config);
    std::string line;
    std::string key_1;
    std::string key_2;
    std::string val;
    while (getline(f, line)) {
        if (line.empty()) {
            continue;
        }
        else if (line[0] != ' ' and line[1] != ' ') {
            key_1 = line;
            key_1.pop_back();

            //std::cout << "key_1 = " << key_1 << std::endl;
        }
        else {
            std::istringstream ss(line);
            ss >> key_2 >> val;
            key_2.pop_back();

            //std::cout << "key_2 = " << key_2 << std::endl;
            //std::cout << "val = " << val << std::endl;

            config[key_1][key_2] = val;
        }
    }


}

void ConfigManager::print_config() {

    std::cout << "Config:" << std::endl;
    for (auto& item_global : config) {
        std::string global_key = item_global.first;
        std::cout << global_key << ":" << std::endl;
        for (auto& item_local : item_global.second) {
            std::string local_key = item_local.first;
            std::string value = item_local.second;
            std::cout << "  " << local_key << ": " << value << std::endl;
        }
    }
}

std::string ConfigManager::readout_string(const std::string& global_key,
                                          const std::string& local_key) {

    std::string value = config.at(global_key).at(local_key);
    if (value.empty()) {
        throw std::runtime_error("Wrong " + local_key + "!");
    }

    return value;
}

std::string ConfigManager::readout_string(const std::string& global_key,
                                          const std::string& local_key,
                                          const std::vector<std::string>& valid) {

    std::string value = readout_string(global_key, local_key);
    if (std::find(valid.begin(), valid.end(), value) != valid.end()) {
        return value;
    }
    else {
        throw std::runtime_error("Wrong " + local_key + "!");
    }

    return value;
}

bool ConfigManager::readout_bool(const std::string& global_key,
                                 const std::string& local_key) {

    std::string value = config.at(global_key).at(local_key);
    if (value == "true") {
        return true;
    }
    else if (value == "false") {
        return false;
    }
    else {
        throw std::runtime_error("Wrong " + local_key + "!");
    }
}

double ConfigManager::readout_double(const std::string& global_key,
                                     const std::string& local_key,
                                     const std::vector<double>& minmax) {

    double value = std::stod(config.at(global_key).at(local_key));
    if (value < minmax[0] || value > minmax[1]) {
        throw std::runtime_error("Wrong " + local_key + "!");
    }

    return value;
}

size_t ConfigManager::readout_int(const std::string& global_key,
                                     const std::string& local_key,
                                     const std::vector<size_t>& minmax) {

    size_t value = std::stoi(config.at(global_key).at(local_key));
    if (value < minmax[0] || value > minmax[1]) {
        throw std::runtime_error("Wrong " + local_key + "!");
    }

    return value;
}


void ConfigManager::validate_config() {

    try {

        /*
         * INFO
         */

        verbose = readout_bool(std::string("info"), std::string("verbose"));
        prefix = readout_string(std::string("info"), std::string("prefix"));
        multidir = readout_bool(std::string("info"), std::string("multidir"));
        path_to_project = readout_string(std::string("info"), std::string("path_to_project"));
        path_to_python_interpreter = readout_string(std::string("info"), std::string("path_to_python_interpreter"));
        global_root_dir = readout_string(std::string("info"), std::string("global_root_dir"));
        global_results_dir_name = readout_string(std::string("info"), std::string("global_results_dir_name"));
        ionization_tables_dir_name = readout_string(std::string("info"), std::string("ionization_tables_dir_name"));

        /*
         * EQUATION
         */

        // diffraction
        bool diffraction = readout_bool(std::string("equation"), std::string("diffraction"));
        if (diffraction) { active_linear_terms.emplace_back("diffraction"); }

        // dispersion
        bool dispersion_full = readout_bool(std::string("equation"), std::string("dispersion_full"));
        dispersion_gvd_sweep = readout_bool(std::string("equation"), std::string("dispersion_gvd_sweep"));
        bool dispersion_gvd_fft = readout_bool(std::string("equation"), std::string("dispersion_gvd_fft"));

        if (dispersion_full && !dispersion_gvd_sweep && !dispersion_gvd_fft) {
            active_linear_terms.emplace_back("dispersion_full");
        }
        else if (!dispersion_full && dispersion_gvd_sweep && !dispersion_gvd_fft) {
            active_linear_terms.emplace_back("dispersion_gvd");
        }
        else if (!dispersion_full && !dispersion_gvd_sweep && dispersion_gvd_fft) {
            active_linear_terms.emplace_back("dispersion_gvd_fft");
        }
        else if ((dispersion_full && dispersion_gvd_sweep) ||
                 (dispersion_full && dispersion_gvd_fft) ||
                 (dispersion_gvd_sweep && dispersion_gvd_fft)) {
            throw std::runtime_error(">1 dispersions in wave equation!");
        }

        // kerr_instant
        bool kerr_instant = readout_bool(std::string("equation"), std::string("kerr_instant"));
        bool kerr_inertial = readout_bool(std::string("equation"), std::string("kerr_inertial"));

        kerr_info.insert({"instant", kerr_instant});
        kerr_info.insert({"inertial", kerr_inertial});
        if (kerr_instant || kerr_inertial) { active_nonlinear_terms.emplace_back("kerr"); }

        // plasma
        bool plasma = readout_bool(std::string("equation"), std::string("plasma"));
        if (plasma) { active_nonlinear_terms.emplace_back("plasma"); }

        // bremsstrahlung
        bool bremsstrahlung = readout_bool(std::string("equation"), std::string("bremsstrahlung"));
        if (bremsstrahlung) { active_nonlinear_terms.emplace_back("bremsstrahlung"); }

        // dissipation
        bool dissipation = readout_bool(std::string("equation"), std::string("dissipation"));
        if (dissipation) { active_nonlinear_terms.emplace_back("dissipation"); }


        /*
         * T
         */

        // diffraction
        bool T_diffraction = readout_bool(std::string("T"), std::string("diffraction"));
        T.insert({"diffraction", T_diffraction});

        // dispersion
        bool T_dispersion = readout_bool(std::string("T"), std::string("dispersion"));
        T.insert({"dispersion", T_dispersion});

        // kerr
        bool T_kerr = readout_bool(std::string("T"), std::string("kerr"));
        T.insert({"kerr", T_kerr});

        // plasma
        bool T_plasma = readout_bool(std::string("T"), std::string("plasma"));
        T.insert({"plasma", T_plasma});

        // bremsstrahlung
        bool T_bremsstrahlung = readout_bool(std::string("T"), std::string("bremsstrahlung"));
        T.insert({"bremsstrahlung", T_bremsstrahlung});

        /*
         * MEDIUM
         */

        medium = readout_string(std::string("medium"), std::string("name"), {"SiO2", "CaF2", "LiF"});
        ionization = readout_string(std::string("medium"), std::string("ionization"), {"OriginalKeldysh", "SmoothedKeldysh"});

        /*
         * PULSED_BEAM
         */
        lambda_0 = readout_double(std::string("pulsed_beam"), std::string("lambda_0"), {300e-9, 5e-6});
        r_0 = readout_double(std::string("pulsed_beam"), std::string("r_0"), {10e-6, 500e-6});
        t_0 = readout_double(std::string("pulsed_beam"), std::string("t_0"), {10e-15, 200e-15});
        M = readout_int(std::string("pulsed_beam"), std::string("M"), {0, 5});
        m = readout_int(std::string("pulsed_beam"), std::string("m"), {0, 5});
        p_0_to_p_cr = readout_double(std::string("pulsed_beam"), std::string("p_0_to_p_cr"), {0.1, 500});

        /*
         * GRID
         */

        n_r = readout_int(std::string("grid"), std::string("n_r"), {128, 16000});
        n_t = readout_int(std::string("grid"), std::string("n_t"), {128, 32000});

        /*
         * TRACK
         */

        n_z = readout_int(std::string("track"), std::string("n_z"), {1, 100000});
        dz_0 = readout_double(std::string("track"), std::string("dz_0"), {1e-10, 1});
        print_current_state_every = readout_int(std::string("track"), std::string("print_current_state_every"), {0, 100000});
        save_every = readout_int(std::string("track"), std::string("save_every"), {0, 100000});
        save_field = readout_bool(std::string("track"), std::string("save_field"));
        save_plasma = readout_bool(std::string("track"), std::string("save_plasma"));

        /*
         * PLOT
         */

        plot_intensity_rt = readout_bool(std::string("plot"), std::string("plot_intensity_rt"));
        plot_plasma_rt = readout_bool(std::string("plot"), std::string("plot_plasma_rt"));
        plot_track = readout_bool(std::string("plot"), std::string("plot_track"));

        /*
         * OTHER
         */
        num_threads = readout_int(std::string("other"), std::string("num_threads"), {1, (size_t)omp_get_num_procs()});

    }
    catch (std::runtime_error &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        exit(-1);
    }

}

//
// Created by vasilyev on 07.08.2019.
//

#include "config_manager.h"

#include <sstream>
#include <fstream>


ConfigManager::ConfigManager() = default;
ConfigManager::~ConfigManager() = default;

void ConfigManager::parse_and_validate_config(std::string &path_to_config) {
    parse_config(path_to_config);
    validate_config();
}

void ConfigManager::parse_config(std::string& path_to_config) {

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

void ConfigManager::validate_config() {

    try {

        // info
        prefix = config.at("info").at("prefix");
        if (prefix.empty()) {
            throw std::runtime_error("Wrong prefix!");
        }

        path_to_project = config.at("info").at("path_to_project");
        if (path_to_project.empty()) {
            throw std::runtime_error("Wrong path_to_project!");
        }

        path_to_python_interpreter = config.at("info").at("path_to_python_interpreter");
        if (path_to_python_interpreter.empty()) {
            throw std::runtime_error("Wrong path_to_python_interpreter!");
        }

        global_root_dir = config.at("info").at("global_root_dir");
        if (global_root_dir.empty()) {
            throw std::runtime_error("Wrong global_root_dir!");
        }

        global_results_dir_name = config.at("info").at("global_results_dir_name");
        if (global_results_dir_name.empty()) {
            throw std::runtime_error("Wrong global_results_dir_name!");
        }

        ionization_tables_dir_name = config.at("info").at("ionization_tables_dir_name");
        if (ionization_tables_dir_name.empty()) {
            throw std::runtime_error("Wrong ionization_tables_dir_name!");
        }


        // medium
        medium = config.at("medium").at("type");
        if (medium != "SiO2" && medium != "CaF2" && medium != "LiF") {
            throw std::runtime_error("Wrong medium!");
        }

        // pulsed_beam

        lambda_0 = std::stod(config.at("pulsed_beam").at("lambda_0"));
        if (lambda_0 < 300e-9 || lambda_0 > 5e-6) {
            throw std::runtime_error("Wrong lambda_0!");
        }

        r_0 = std::stod(config.at("pulsed_beam").at("r_0"));
        if (r_0 < 10e-6 || r_0 > 500e-6) {
            throw std::runtime_error("Wrong r_0!");
        }

        t_0 = std::stod(config.at("pulsed_beam").at("t_0"));
        if (t_0 < 10e-15 || t_0 > 200e-15) {
            throw std::runtime_error("Wrong t_0!");
        }

        M = std::stoi(config.at("pulsed_beam").at("M"));
        if (M < 0 || M > 5) {
            throw std::runtime_error("Wrong M!");
        }

        m = std::stoi(config.at("pulsed_beam").at("m"));
        if (m < -5 || m > 5) {
            throw std::runtime_error("Wrong m!");
        }

        // grid

        n_r = std::stoi(config.at("grid").at("n_r"));
        if (n_r < 1 || n_r > 16000) {
            throw std::runtime_error("Wrong n_r!");
        }

        n_t = std::stoi(config.at("grid").at("n_t"));
        if (n_t < 1 || n_t > 32000) {
            throw std::runtime_error("Wrong n_t!");
        }

        // track

        n_z = std::stoi(config.at("track").at("n_z"));
        if (n_z < 1 || n_z > 100000) {
            throw std::runtime_error("Wrong n_z!");
        }

        dz_0 = std::stod(config.at("track").at("dz_0"));
        if (dz_0 < 1e-10 || dz_0 > 1) {
            throw std::runtime_error("Wrong dz_0!");
        }

        print_current_state_every = std::stoi(config.at("track").at("print_current_state_every"));
        if (print_current_state_every < 0) {
            throw std::runtime_error("Wrong print_current_state_every!");
        }

        save_every = std::stoi(config.at("track").at("save_every"));
        if (save_every < 0) {
            throw std::runtime_error("Wrong save_every!");
        }

        if (config.at("track").at("save_field") == "true") {
            save_field = true;
        }
        else if (config.at("track").at("save_field") == "false") {
            save_field = false;
        }
        else {
            throw std::runtime_error("Wrong save_field!");
        }

        if (config.at("track").at("save_plasma") == "true") {
            save_plasma = true;
        }
        else if (config.at("track").at("save_plasma") == "false") {
            save_plasma = false;
        }
        else {
            throw std::runtime_error("Wrong save_plasma!");
        }


        // plot

        if (config.at("plot").at("plot_intensity_rt") == "true") {
            plot_intensity_rt = true;
        }
        else if (config.at("plot").at("plot_intensity_rt") == "false") {
            plot_intensity_rt = false;
        }
        else {
            throw std::runtime_error("Wrong plot_intensity_rt!");
        }

        if (config.at("plot").at("plot_plasma_rt") == "true") {
            plot_plasma_rt = true;
        }
        else if (config.at("plot").at("plot_plasma_rt") == "false") {
            plot_plasma_rt = false;
        }
        else {
            throw std::runtime_error("Wrong plot_plasma_rt!");
        }

        if (config.at("plot").at("plot_track") == "true") {
            plot_track = true;
        }
        else if (config.at("plot").at("plot_track") == "false") {
            plot_track = false;
        }
        else {
            throw std::runtime_error("Wrong plot_track!");
        }


    }
    catch (std::runtime_error &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        exit(-1);
    }





}

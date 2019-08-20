//
// Created by vasilyev on 07.08.2019.
//

#include "config_manager.h"

#include <sstream>
#include <fstream>
#include <omp.h>



ConfigManager::ConfigManager() = default;

ConfigManager::ConfigManager(std::string& _path_to_config)
: path_to_config(_path_to_config) {}

ConfigManager::~ConfigManager() = default;

void ConfigManager::parse_and_validate_config() {
    parse_config();
    validate_config();
}

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

void ConfigManager::validate_config() {

    try {

        /*
         * INFO
         */

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

        /*
         * EQUATION
         */

        // diffraction
        bool diffraction;
        if (config.at("equation").at("diffraction") == "true") {
            diffraction = true;
        }
        else if (config.at("equation").at("diffraction") == "false") {
            diffraction = false;
        }
        else {
            throw std::runtime_error("Wrong diffraction!");
        }
        if (diffraction) {
            active_linear_terms.emplace_back("diffraction");
        }

        // dispersion
        bool dispersion_full;
        if (config.at("equation").at("dispersion_full") == "true") {
            dispersion_full = true;
        }
        else if (config.at("equation").at("dispersion_full") == "false") {
            dispersion_full = false;
        }
        else {
            throw std::runtime_error("Wrong dispersion_full!");
        }

        bool dispersion_gvd;
        if (config.at("equation").at("dispersion_gvd") == "true") {
            dispersion_gvd = true;
        }
        else if (config.at("equation").at("dispersion_gvd") == "false") {
            dispersion_gvd = false;
        }
        else {
            throw std::runtime_error("Wrong dispersion_gvd!");
        }

        if (dispersion_full && !dispersion_gvd) {
            active_linear_terms.emplace_back("dispersion_full");
        }
        else if (!dispersion_full && dispersion_gvd) {
            active_linear_terms.emplace_back("dispersion_gvd");
        }
        else if (dispersion_full && dispersion_gvd) {
            throw std::runtime_error("Two dispersions in wave equation!");
        }

        // kerr_instant
        bool kerr_instant;
        if (config.at("equation").at("kerr_instant") == "true") {
            kerr_instant = true;
        }
        else if (config.at("equation").at("kerr_instant") == "false") {
            kerr_instant = false;
        }
        else {
            throw std::runtime_error("Wrong kerr_instant!");
        }

        // kerr_inertial
        bool kerr_inertial;
        if (config.at("equation").at("kerr_inertial") == "true") {
            kerr_inertial = true;
        }
        else if (config.at("equation").at("kerr_inertial") == "false") {
            kerr_inertial = false;
        }
        else {
            throw std::runtime_error("Wrong kerr_inertial!");
        }

        kerr_info.insert({"instant", kerr_instant});
        kerr_info.insert({"inertial", kerr_inertial});
        if (kerr_instant || kerr_inertial) {
            active_nonlinear_terms.emplace_back("kerr");
        }

        // plasma
        bool plasma;
        if (config.at("equation").at("plasma") == "true") {
            plasma = true;
        }
        else if (config.at("equation").at("plasma") == "false") {
            plasma = false;
        }
        else {
            throw std::runtime_error("Wrong plasma!");
        }
        if (plasma) {
            active_nonlinear_terms.emplace_back("plasma");
        }

        // bremsstrahlung
        bool bremsstrahlung;
        if (config.at("equation").at("bremsstrahlung") == "true") {
            bremsstrahlung = true;
        }
        else if (config.at("equation").at("bremsstrahlung") == "false") {
            bremsstrahlung = false;
        }
        else {
            throw std::runtime_error("Wrong bremsstrahlung!");
        }
        if (bremsstrahlung) {
            active_nonlinear_terms.emplace_back("bremsstrahlung");
        }

        // dissipation
        bool dissipation;
        if (config.at("equation").at("dissipation") == "true") {
            dissipation = true;
        }
        else if (config.at("equation").at("dissipation") == "false") {
            dissipation = false;
        }
        else {
            throw std::runtime_error("Wrong dissipation!");
        }
        if (dissipation) {
            active_nonlinear_terms.emplace_back("dissipation");
        }


        /*
         * T
         */

        // diffraction
        bool T_diffraction;
        if (config.at("T").at("diffraction") == "true") {
            T_diffraction = true;
        }
        else if (config.at("T").at("diffraction") == "false") {
            T_diffraction = false;
        }
        else {
            throw std::runtime_error("Wrong T_diffraction!");
        }
        T.insert({"diffraction", T_diffraction});

        // dispersion
        bool T_dispersion;
        if (config.at("T").at("dispersion") == "true") {
            T_dispersion = true;
        }
        else if (config.at("T").at("dispersion") == "false") {
            T_dispersion = false;
        }
        else {
            throw std::runtime_error("Wrong T_dispersion!");
        }
        T.insert({"dispersion", T_dispersion});

        // kerr
        bool T_kerr;
        if (config.at("T").at("kerr") == "true") {
            T_kerr = true;
        }
        else if (config.at("T").at("kerr") == "false") {
            T_kerr = false;
        }
        else {
            throw std::runtime_error("Wrong T_kerr!");
        }
        T.insert({"kerr", T_kerr});

        // plasma
        bool T_plasma;
        if (config.at("T").at("plasma") == "true") {
            T_plasma = true;
        }
        else if (config.at("T").at("plasma") == "false") {
            T_plasma = false;
        }
        else {
            throw std::runtime_error("Wrong T_plasma!");
        }
        T.insert({"plasma", T_plasma});

        // bremsstrahlung
        bool T_bremsstrahlung;
        if (config.at("T").at("bremsstrahlung") == "true") {
            T_bremsstrahlung = true;
        }
        else if (config.at("T").at("bremsstrahlung") == "false") {
            T_bremsstrahlung = false;
        }
        else {
            throw std::runtime_error("Wrong T_plasma!");
        }
        T.insert({"bremsstrahlung", T_bremsstrahlung});

        /*
         * MEDIUM
         */

        medium = config.at("medium").at("material");
        if (medium != "SiO2" && medium != "CaF2" && medium != "LiF") {
            throw std::runtime_error("Wrong medium!");
        }

        ionization = config.at("medium").at("ionization");
        if (ionization != "OriginalKeldysh" && ionization != "SmoothedKeldysh") {
            throw std::runtime_error("Wrong ionization!");
        }


        /*
         * PULSED_BEAM
         */

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
        if (m < 0 || m > 5) {
            throw std::runtime_error("Wrong m!");
        }

        p_0_to_p_cr = std::stod(config.at("pulsed_beam").at("p_0_to_p_cr"));
        if (p_0_to_p_cr < 0.1 || p_0_to_p_cr > 500) {
            throw std::runtime_error("Wrong p_0_to_p_cr!");
        }

        /*
         * GRID
         */

        n_r = std::stoi(config.at("grid").at("n_r"));
        if (n_r < 1 || n_r > 16000) {
            throw std::runtime_error("Wrong n_r!");
        }

        n_t = std::stoi(config.at("grid").at("n_t"));
        if (n_t < 1 || n_t > 32000) {
            throw std::runtime_error("Wrong n_t!");
        }

        /*
         * TRACK
         */

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

        /*
         * PLOT
         */

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

        /*
         * OTHER
         */

        num_threads = std::stoi(config.at("other").at("num_threads"));
        if (num_threads < 1 or num_threads > omp_get_num_procs()) {
            throw std::runtime_error("Wrong num_threads!");
        }


    }
    catch (std::runtime_error &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        exit(-1);
    }





}

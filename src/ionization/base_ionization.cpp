//
// Created by vasilyev on 28.07.2019.
//

#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>

#include "base_ionization.h"



BaseIonization::BaseIonization() {
    n_i = 500000;
    i_start = 5e14;
    i_step = 1e13;
}


BaseIonization::~BaseIonization() = default;


std::string BaseIonization::generate_ionization_table_name(std::string& medium_name, double lambda_0) {
    std::ostringstream ss;
    ss << name << "_" << medium_name << "_" << lambda_0 * 1e9;
    std::string ionization_table_name = ss.str();

    return ionization_table_name;
}



void BaseIonization::make_ionization_table(std::string& path_to_ionization_table) {
    std::ofstream f(path_to_ionization_table);

    for(size_t step = 0; step < n_i; ++step) {
        double i = i_start + step * i_step;
        double rate = calculate_R(i);

        f << std::scientific;
        f << i << "    " << rate << "\n";
    }

    f.close();
}


void BaseIonization::process_ionization_table(
        ConfigManager& config_manager,
        std::string& path_to_ionization_table) {

    std::string path_to_project = config_manager.path_to_project;
    std::string path_to_python_interpreter = config_manager.path_to_python_interpreter;

    std::string execute = path_to_python_interpreter + " " + path_to_project + "/processing/scripts/ionization.py " +
            "--path_to_ionization_table=" + path_to_ionization_table;
    std::cout << execute << std::endl;
    std::system(execute.c_str());

}

void BaseIonization::initialize_ionization_table(ConfigManager& config_manager,
                                                 double lambda_0) {

    std::string ionization_table_name = generate_ionization_table_name(config_manager.medium, lambda_0);
    std::string path_to_ionization_table = config_manager.global_root_dir + "/" +
            config_manager.ionization_tables_dir_name + "/" + ionization_table_name;

    std::ifstream f(path_to_ionization_table.c_str());
    if (f.good()) {
        std::cout << "ionization table exists!" << std::endl;
    }
    else {
        std::cout << "ionization table doesn't exist!" << std::endl;
        make_ionization_table(path_to_ionization_table);

        // create new plot of ionization rates
        process_ionization_table(config_manager, path_to_ionization_table);
    }

    // create data structure with rates array
    rates = std::vector<double>(n_i, 0.0);
    std::string line;
    size_t i = 0;
    while (std::getline(f, line)) {
        double col1, col2;
        std::istringstream ss(line);
        ss >> col1;
        char c = ss.peek();
        while (!std::isdigit(c)) {
            ss.get();
            c = ss.peek();
        }
        ss >> col2;
        rates[i] = col2;

        i += 1;
    }

    f.close();
}


double BaseIonization::R(double i) {
    if (i < i_start) {
        return 0.0;
    }
    else {
        return rates[std::min((size_t)((i - i_start) / i_step), n_i - 1)];
    }
}

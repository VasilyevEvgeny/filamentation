//
// Created by vasilyev on 28.07.2019.
//

#include <fstream>
#include <sstream>

#include "base_ionization.h"


BaseIonization::BaseIonization() = default;

BaseIonization::~BaseIonization() = default;


void BaseIonization::make_ionization_table(std::string& path_to_ionization_tables_dir, std::string& medium_name, double lambda_0) {

    std::ostringstream ss;
    ss << name << "_" << medium_name << "_" << lambda_0 * 1e9;
    std::string ionization_table_name = ss.str();

    std::ofstream f(path_to_ionization_tables_dir + "/" + ionization_table_name);

    long int step_max = 500000;
    double i_start = 5e14;
    double di = 1e13;

    for(size_t step = 0; step < step_max; ++step) {
        double i = i_start + step * di;
        double rate = R(i);

        f << std::scientific;
        f << i << "    " << rate << "\n";
    }

    f.close();

}
//
// Created by vasilyev on 28.07.2019.
//

#include <fstream>
#include <iostream>
#include <sstream>

#include "base_ionization.h"



BaseIonization::BaseIonization() {
    step_max = 500000;
    i_start = 5e14;
    di = 1e13;
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

    for(size_t step = 0; step < step_max; ++step) {
        double i = i_start + step * di;
        double rate = R(i);

        f << std::scientific;
        f << i << "    " << rate << "\n";
    }

    f.close();
}


void BaseIonization::process_ionization_table(std::map<std::string, std::string>& args, std::string& path_to_ionization_table) {

    std::string path_to_project = args["path_to_project"];
    std::string path_to_python_interpreter = args["python_interpreter"];

    std::string execute = path_to_python_interpreter + " " + path_to_project + "/processing/scripts/ionization.py " +
            "--path_to_ionization_table=" + path_to_ionization_table;
    std::cout << execute << std::endl;
    std::system(execute.c_str());

}

void BaseIonization::initialize_ionization_table(std::map<std::string, std::string>& args,
                                                 std::string& path_to_ionization_tables_dir,
                                                 std::string& medium_name,
                                                 double lambda_0) {

    std::string ionization_table_name = generate_ionization_table_name(medium_name, lambda_0);
    std::string path_to_ionization_table = path_to_ionization_tables_dir + "/" + ionization_table_name;

    std::ifstream f(path_to_ionization_table.c_str());
    if (f.good()) {
        std::cout << "ionization table exists!" << std::endl;
    }
    else {
        std::cout << "ionization table doesn't exist!" << std::endl;
        make_ionization_table(path_to_ionization_table);
    }

    // create data structure with rates array
    // ...

    // plot ionization rates
    process_ionization_table(args, path_to_ionization_table);

}




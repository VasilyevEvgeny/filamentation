//
// Created by vasilyev on 07.08.2019.
//

#ifndef FILAMENTATION_CONFIGMANAGER_H
#define FILAMENTATION_CONFIGMANAGER_H

#include <iostream>
#include <map>

class ConfigManager {
public:
    ConfigManager();

    ~ConfigManager();

    void parse_and_validate_config(std::string& path_to_config);
    void parse_config(std::string& path_to_config);
    void print_config();
    void validate_config();

    std::map<std::string, std::map<std::string, std::string>> config;

    // info
    std::string prefix;
    std::string path_to_project;
    std::string path_to_python_interpreter;
    std::string global_root_dir;
    std::string global_results_dir_name;
    std::string ionization_tables_dir_name;

    //medium
    std::string medium;

    // pulsed_beam
    double lambda_0;
    double r_0;
    double t_0;
    double M;
    double m;

    // grid
    int n_r;
    int n_t;

    // track
    int n_z;
    double dz_0;
    int print_current_state_every;
    int save_every;
    bool save_field;
    bool save_plasma;

    // plot
    bool plot_intensity_rt;
    bool plot_plasma_rt;
    bool plot_track;


};


#endif //FILAMENTATION_CONFIGMANAGER_H

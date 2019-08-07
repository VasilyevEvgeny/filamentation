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
    explicit ConfigManager(std::string& _path_to_config);

    ~ConfigManager();

    void parse_and_validate_config();
    void parse_config();
    void print_config();
    void validate_config();
    void initialize_subconfigs();

    std::string path_to_config;
    std::map<std::string, std::map<std::string, std::string>> config;
    std::map<std::string, std::string> config_info;
    std::map<std::string, bool> config_plot;

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
    size_t M;
    size_t m;
    double p_0_to_p_cr;

    // grid
    size_t n_r;
    size_t n_t;

    // track
    size_t n_z;
    double dz_0;
    size_t print_current_state_every;
    size_t save_every;
    bool save_field;
    bool save_plasma;

    // plot
    bool plot_intensity_rt;
    bool plot_plasma_rt;
    bool plot_track;

    // other
    size_t num_threads;


};


#endif //FILAMENTATION_CONFIGMANAGER_H

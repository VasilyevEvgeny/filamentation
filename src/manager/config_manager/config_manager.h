//
// Created by vasilyev on 07.08.2019.
//

#ifndef FILAMENTATION_CONFIGMANAGER_H
#define FILAMENTATION_CONFIGMANAGER_H

#include <iostream>
#include <map>
#include <vector>


class ConfigManager {
public:
    ConfigManager();
    explicit ConfigManager(const std::string& _path_to_config);

    ~ConfigManager();

    void parse_config();
    void print_config();
    void validate_config();

    std::string path_to_config;
    std::map<std::string, std::map<std::string, std::string>> config;

    // readout
    std::string readout_string(const std::string& global_key, const std::string& local_key);
    std::string readout_string(const std::string& global_key, const std::string& local_key, const std::vector<std::string>& valid);
    bool readout_bool(const std::string& global_key, const std::string& local_key);
    double readout_double(const std::string& global_key, const std::string& local_key, const std::vector<double>& minmax);
    size_t readout_int(const std::string& global_key, const std::string& local_key, const std::vector<size_t>& minmax);

    // info
    bool verbose;
    std::string prefix;
    bool multidir;
    std::string path_to_project;
    std::string path_to_python_interpreter;
    std::string global_root_dir;
    std::string global_results_dir_name;
    std::string ionization_tables_dir_name;

    // equation
    std::vector<std::string> active_linear_terms;
    std::vector<std::string> active_nonlinear_terms;
    bool dispersion_gvd_sweep;
    std::map<std::string, bool> T;
    std::map<std::string, bool> kerr_info;
    bool with_plasma;

    //medium
    std::string medium;
    std::string ionization;

    // pulsed_beam
    double lambda_0;
    double r_0;
    double t_0;
    size_t M;
    size_t m;
    double P_0_to_P_cr;

    // grid
    size_t n_r;
    size_t n_t;

    // track
    size_t n_z;
    double dz_0;
    double max_intensity_to_stop;
    double phase_increment_min;
    double phase_increment_max;
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

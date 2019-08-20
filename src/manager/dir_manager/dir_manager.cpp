//
// Created by vasilyev on 29.06.2019.
//

#include <stdexcept>
#include <ctime>

#include "dir_manager.h"



DirManager::DirManager(ConfigManager& _config_manager) {
    global_results_dir = _config_manager.global_root_dir + "/" + _config_manager.global_results_dir_name;
    ionization_tables_dir = _config_manager.global_root_dir + "/" + _config_manager.ionization_tables_dir_name;

    current_results_dir_name = _config_manager.prefix + "_" + get_current_datetime();
    current_results_dir = global_results_dir + "/" + current_results_dir_name;

    field_dir_name = "field";
    field_dir = current_results_dir + "/" + field_dir_name;

    plasma_dir_name = "plasma";
    plasma_dir = current_results_dir + "/" + plasma_dir_name;

    try {
        _mkdir(global_results_dir.c_str());
        _mkdir(ionization_tables_dir.c_str());

        if (_mkdir(current_results_dir.c_str())) {
            throw std::runtime_error("current_results_dir wasn't created!");
        }

        if (_mkdir(field_dir.c_str())) {
            throw std::runtime_error("field_dir wasn't created!");
        }

        if (_mkdir(plasma_dir.c_str())) {
            throw std::runtime_error("plasma_dir wasn't created!");
        }
    }
    catch(const std::exception &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        exit(-1);
    }
}

DirManager::~DirManager() = default;

std::string DirManager::get_current_datetime() const {
    time_t rawtime;
    struct tm *timeinfo;
    char buffer[80];

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer,sizeof(buffer),"%Y-%m-%d_%H-%M-%S", timeinfo);

    return std::string(buffer);
}


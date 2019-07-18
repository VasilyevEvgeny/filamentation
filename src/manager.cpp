//
// Created by vasilyev on 29.06.2019.
//

#include <stdexcept>
#include <ctime>

#include "manager.h"



Manager::Manager(std::map<std::string, std::string>& args) {
    global_results_dir = args["global_root_dir"] + "/" + args["global_results_dir_name"];

    current_results_dir_name = args["prefix"] + "_" + get_current_datetime();
    current_results_dir = global_results_dir + "/" + current_results_dir_name;

    field_dir_name = "field";
    field_dir = current_results_dir + "/" + field_dir_name;

    try {
        _mkdir(global_results_dir.c_str());

        if (_mkdir(current_results_dir.c_str())) {
            throw std::runtime_error("current_results_dir wasn't created!");
        }

        if (_mkdir(field_dir.c_str())) {
            throw std::runtime_error("field_dir wasn't created!");
        }
    }
    catch(const std::exception &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        exit(-1);
    }
}

Manager::~Manager() = default;

std::string Manager::get_current_datetime() const {
    time_t rawtime;
    struct tm *timeinfo;
    char buffer[80];

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer,sizeof(buffer),"%Y-%m-%d_%H-%M-%S", timeinfo);

    return std::string(buffer);
}

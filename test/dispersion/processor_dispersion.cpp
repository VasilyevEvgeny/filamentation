//
// Created by vasilyev on 24.07.2019.
//

#include "processor_dispersion.h"

ProcessorDispersion::ProcessorDispersion() = default;

ProcessorDispersion::ProcessorDispersion(ConfigManager& _config_manager, DirManager& _dir_manager)
: Postprocessor(_config_manager, _dir_manager){

    path_to_test_script = "/processing/test/dispersion.py";

}

ProcessorDispersion::~ProcessorDispersion() = default;



void ProcessorDispersion::go() {

    std::string execute = path_to_python_interpreter + " " + path_to_project + path_to_test_script + " " +
                          "--current_results_dir=" + manager.current_results_dir;
    std::cout << execute << std::endl;
    std::system(execute.c_str());

}
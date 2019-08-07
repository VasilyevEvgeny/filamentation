//
// Created by vasilyev on 10.07.2019.
//

#include <direct.h>
#include <iostream>
#include <algorithm>

#include "processor.h"

Processor::Processor() = default;

Processor::Processor(ConfigManager& config_manager,
                     DirManager& _manager)
: manager(_manager) {

    path_to_project = config_manager.path_to_project;
    path_to_python_interpreter = config_manager.path_to_python_interpreter;

    plot_intensity_rt = config_manager.plot_intensity_rt;
    plot_plasma_rt = config_manager.plot_plasma_rt;
    plot_track = config_manager.plot_track;
}


void Processor::go() {
    if (plot_intensity_rt) {
        std::string execute = path_to_python_interpreter + " " + path_to_project + "/processing/scripts/intensity_rt.py " +
                              "--current_results_dir=" + manager.current_results_dir;
        std::cout << execute << std::endl;
        std::system(execute.c_str());
    }
    if (plot_plasma_rt) {
        std::string execute = path_to_python_interpreter + " " + path_to_project + "/processing/scripts/plasma_rt.py " +
                              "--current_results_dir=" + manager.current_results_dir;
        std::cout << execute << std::endl;
        std::system(execute.c_str());
    }
    if (plot_track) {
        std::string execute = path_to_python_interpreter + " " + path_to_project + "/processing/scripts/track.py " +
                              "--current_results_dir=" + manager.current_results_dir;
        std::cout << execute << std::endl;
        std::system(execute.c_str());
    }
}



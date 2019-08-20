//
// Created by vasilyev on 10.07.2019.
//

#include <direct.h>
#include <iostream>
#include <algorithm>

#include "postprocessor.h"

Postprocessor::Postprocessor() = default;

Postprocessor::Postprocessor(ConfigManager& _config_manager,
                     DirManager& _dir_manager,
                     std::shared_ptr<Logger>& _logger)
: dir_manager(_dir_manager)
, logger(_logger) {

    logger->add_propagation_event(std::string("creating postprocessor"));

    path_to_project = _config_manager.path_to_project;
    path_to_python_interpreter = _config_manager.path_to_python_interpreter;

    plot_intensity_rt = _config_manager.plot_intensity_rt;
    plot_plasma_rt = _config_manager.plot_plasma_rt;
    plot_track = _config_manager.plot_track;

}

Postprocessor::~Postprocessor() = default;


void Postprocessor::go() {
    if (plot_intensity_rt) {
        std::string execute = path_to_python_interpreter + " " + path_to_project + "/processing/scripts/intensity_rt.py " +
                              "--current_results_dir=" + dir_manager.current_results_dir;
        std::cout << execute << std::endl;
        std::system(execute.c_str());
    }
    if (plot_plasma_rt) {
        std::string execute = path_to_python_interpreter + " " + path_to_project + "/processing/scripts/plasma_rt.py " +
                              "--current_results_dir=" + dir_manager.current_results_dir;
        std::cout << execute << std::endl;
        std::system(execute.c_str());
    }
    if (plot_track) {
        std::string execute = path_to_python_interpreter + " " + path_to_project + "/processing/scripts/track.py " +
                              "--current_results_dir=" + dir_manager.current_results_dir;
        std::cout << execute << std::endl;
        std::system(execute.c_str());
    }
}



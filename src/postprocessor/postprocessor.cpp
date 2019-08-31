//
// Created by vasilyev on 10.07.2019.
//

#include <direct.h>
#include <iostream>
#include <algorithm>
#include <chrono>

#include "postprocessor.h"
#include "misc/misc.h"

Postprocessor::Postprocessor() = default;

Postprocessor::Postprocessor(ConfigManager& _config_manager) {
    path_to_project = _config_manager.path_to_project;
    path_to_python_interpreter = _config_manager.path_to_python_interpreter;

    plot_intensity_rt = _config_manager.plot_intensity_rt;
    plot_plasma_rt = _config_manager.plot_plasma_rt;
    plot_track = _config_manager.plot_track;

}

Postprocessor::~Postprocessor() = default;


void Postprocessor::postprocess(DirManager& dir_manager,
                                std::shared_ptr<Logger>& logger,
                                const std::string& module,
                                const std::string& path_to_script,
                                const std::string& log_info) {
    logger->add_propagation_event(log_info);

    std::string execute = path_to_python_interpreter + " " + path_to_project + "/" + path_to_script + " " +
                          "--current_results_dir=" + dir_manager.current_results_dir;

    auto t_start = TIME::now();
    std::system(execute.c_str());
    auto t_end = TIME::now();
    logger->term_times[module] += logger->duration(t_start, t_end);
}

void Postprocessor::go(DirManager& dir_manager, std::shared_ptr<Logger>& logger) {

    logger->add_propagation_event(std::string("postprocessing"));

    if (plot_intensity_rt) {
        postprocess(dir_manager,
                    logger,
                    std::string("plot_intensity_rt"),
                    std::string("processing/scripts/analysis/intensity_rt_flat.py"),
                    std::string("....plotting I(r,t)"));
    }
//    if (plot_plasma_rt) {
//        postprocess(dir_manager,
//                    logger,
//                    std::string("plot_plasma_rt"),
//                    std::string("processing/scripts/intensity_rt_flat.py"),
//                    std::string("....plotting N_e(r,t)"));
//    }
//    if (plot_track) {
//        postprocess(dir_manager,
//                    logger,
//                    std::string("plot_track"),
//                    std::string("processing/scripts/track.py"),
//                    std::string("....plotting track"));
//    }
}

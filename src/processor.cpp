//
// Created by vasilyev on 10.07.2019.
//

#include <direct.h>
#include <iostream>
#include <algorithm>

#include "processor.h"

Processor::Processor() = default;

Processor::Processor(std::map<std::string, std::string>& args, Manager& _manager) : manager(_manager) {
    path_to_project = args["path_to_project"];
    path_to_python_interpreter = args["python_interpreter"];
    intensity_rt = args["intensity_rt"];
    track = args["track"];
}

std::string Processor::get_cwd() {
    char cCurrentPath[FILENAME_MAX];
//    try {
//        if (_getcwd(cCurrentPath, sizeof(cCurrentPath))) {
    _getcwd(cCurrentPath, sizeof(cCurrentPath));
    cCurrentPath[sizeof(cCurrentPath) - 1] = '\0';
    std::string res = std::string(cCurrentPath);
    std::replace(res.begin(), res.end(), '\\', '/');

    return res;
//        }
//        else {
//            throw std::runtime_error("Problem with get_cwd!");
//        }
//    }
//    catch (std::exception &e) {
//        std::cerr << "Exception: " << e.what() << std::endl;
//    }
}

void Processor::go() {
    if (intensity_rt == "True") {
        std::string execute = path_to_python_interpreter + " " + path_to_project + "/processing/scripts/intensity_rt.py " +
                              "--current_results_dir=" + manager.current_results_dir;
        std::cout << execute << std::endl;
        std::system(execute.c_str());
    }
    if (track == "True") {
        std::string execute = path_to_python_interpreter + " " + path_to_project + "/processing/scripts/track.py " +
                              "--current_results_dir=" + manager.current_results_dir;
        std::cout << execute << std::endl;
        std::system(execute.c_str());
    }
}



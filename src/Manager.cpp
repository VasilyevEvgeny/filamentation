//
// Created by vasilyev on 29.06.2019.
//

#include <stdexcept>

#include "Manager.h"



Manager::Manager(std::map<std::string, std::string>& args) {
    std::string global_results_dir = args["global_root_dir"] + "/" + args["global_results_dir_name"];
    try {
        if (_mkdir(global_results_dir.c_str())) {
            std::string descr = "global";
            throw std::string(descr);
        }
    }
    catch(std::exception &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }


}

Manager::~Manager() {;}

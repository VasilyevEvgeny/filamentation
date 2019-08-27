//
// Created by vasilyev on 26.08.2019.
//

#include <vector>
#include <omp.h>
#include <map>
#include <sstream>
#include <iomanip>

#include "gtest/gtest.h"
#include "logger/logger.h"
#include "pulsed_beam/base_pulsed_beam.h"
#include "manager/config_manager/config_manager.h"
#include "propagator/propagator.h"
#include "misc/misc.h"


int main(int argc, char** argv) {

    // config_manager
    ConfigManager config_manager(std::string("test/marburger/test_marburger_config.yml"));

    // multidir_name
    std::string multidir_name = config_manager.prefix + "_" + get_current_datetime("dir_manager");

    // p_rels
    std::vector<double> p_rels = {2.0, 4.0, 6.0, 8.0, 10.0};

    // main cycle
    for (auto& p_rel : p_rels) {

        std::ostringstream ss;
        ss << std::fixed << std::setw(5) << std::setfill('0') << std::setprecision(2) << p_rel;
        std::string current_results_dir_name = "P_0_to_P_cr=" + ss.str();
        config_manager.P_0_to_P_cr = p_rel;

        // postprocessor
        std::shared_ptr<Postprocessor> postprocessor = std::make_shared<Postprocessor>(config_manager);

        // propagator
        auto propagator = std::make_shared<Propagator>(config_manager,
                                                       postprocessor,
                                                       multidir_name,
                                                       current_results_dir_name);

        // propagate!
        propagator->propagate();

        // delete
        propagator.reset();
        postprocessor.reset();
    }

    std::string multidir = config_manager.global_root_dir + "/" + config_manager.global_results_dir_name + "/" +
                           multidir_name;
    std::string execute = config_manager.path_to_python_interpreter + " " +
                          config_manager.path_to_project + "/" +
                          "processing/test/marburger.py" + " " +
                          "--current_results_dir=" + multidir;

    std::system(execute.c_str());


    return 0;
}

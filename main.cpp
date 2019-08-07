#include <iostream>
#include <fstream>
#include <sstream>
#include <omp.h>
#include <map>
#include <string>
#include <omp.h>

#include "pulsed_beam/base_pulsed_beam/base_pulsed_beam.h"
#include "config_manager.h"
#include "propagator.h"

std::map<std::string, std::string> parse_args(char **argv) {
     return  {{"prefix", argv[1]},
              {"path_to_project", argv[2]},
              {"global_root_dir", argv[3]},
              {"global_results_dir_name", argv[4]},
              {"ionization_tables_dir_name", argv[5]},
              {"python_interpreter", argv[6]},
              {"intensity_rt", argv[7]},
              {"plasma_rt", argv[8]},
              {"track", argv[9]}};
}






int main(int argc, char** argv) {
    std::string path_to_config = "config.yml";
    auto configManager = ConfigManager();
    configManager.parse_and_validate_config(path_to_config);

//    if (config["pulsed_beam"]["lambda_0"] == "SiO2") {
//#ifndef MEDIUM
//#define MEDIUM SiO2
//#endif
//    }
//    else if (config["pulsed_beam"]["lambda_0"] == "CaF2") {
//#ifndef MEDIUM
//#define MEDIUM CaF2
//#endif
//    }
//    else if (config["pulsed_beam"]["lambda_0"] == "LiF") {
//#ifndef MEDIUM
//#define MEDIUM LiF
//#endif
//    }
//    else {
//        throw std::runtime_error("Wrong medium name!");
//    }









//    const size_t NUM_PROCS = omp_get_num_procs();
//
//    std::cout << "NUM_PROCS: " << NUM_PROCS << std::endl;
//
//    omp_set_num_threads(NUM_PROCS);
//
//    auto args = parse_args(argv);
//
//    double lambda_0 = 1800e-9;
//
//    LiF medium(lambda_0);
//
//    std::cout << "Address of medium in main: " << &medium << std::endl;
//
//    Gauss<LiF> pulsed_beam(
//            medium,
//            lambda_0,
////            1,
////            1,
//            100e-6,
//            512,
//            40e-15,
//            1024,
//            5);
//
//    std::cout << "PULSED BEAM ADRESS IN MAIN: " << &pulsed_beam << std::endl;
//
//    Propagator<Gauss<LiF>> propagator(
//            args,
//            pulsed_beam,
//            1,
//            4e-5,
////            std::abs(pulsed_beam.z_diff / 500),
//            10,
//            100
//            );
//
//    propagator.propagate();


    return 0;
}
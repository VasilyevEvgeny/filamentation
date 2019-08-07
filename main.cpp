#include <iostream>
#include <fstream>
#include <sstream>
#include <omp.h>
#include <map>
#include <string>
#include <omp.h>

#include "pulsed_beam/base_pulsed_beam/base_pulsed_beam.h"
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



auto parse_config(std::string& path_to_config) {
    std::map<std::string, std::map<std::string, std::string>> config;

    std::ifstream f(path_to_config);
    std::string line;
    std::string key_1;
    std::string key_2;
    std::string val;
    while (getline(f, line)) {
        if (line.empty()) {
            continue;
        }
        else if (line[0] != ' ' and line[1] != ' ') {
            key_1 = line;
            key_1.pop_back();

            std::cout << "key_1 = " << key_1 << std::endl;
        }
        else {
            std::istringstream ss(line);
            ss >> key_2 >> val;
            key_2.pop_back();

            std::cout << "key_2 = " << key_2 << std::endl;
            std::cout << "val = " << val << std::endl;

            config[key_1][key_2] = val;
        }
    }

    std::cout << "config:" << std::endl;
    for (auto& item_global : config) {
        std::string global_key = item_global.first;
        std::cout << global_key << ":" << std::endl;
        for (auto& item_local : item_global.second) {
            std::string local_key = item_local.first;
            std::string value = item_local.second;
            std::cout << "  " << local_key << ": " << value << std::endl;
        }
    }

}


int main(int argc, char** argv) {
    std::string path_to_config = "config.yml";
    parse_config(path_to_config);

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
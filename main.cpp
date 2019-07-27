#include <iostream>
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
              {"python_interpreter", argv[5]},
              {"intensity_rt", argv[6]},
              {"track", argv[7]}};
}


int main(int argc, char** argv) {

    const size_t NUM_PROCS = omp_get_num_procs();

    std::cout << "NUM_PROCS: " << NUM_PROCS << std::endl;

    omp_set_num_threads(NUM_PROCS);

    auto args = parse_args(argv);

    double lambda_0 = 1800e-9;

    LiF medium(lambda_0);

    std::cout << "Address of medium in main: " << &medium << std::endl;

    Gauss<LiF> pulsed_beam(
            medium,
            lambda_0,
//            1,
//            1,
            100e-6,
            512,
            40e-15,
            1024,
            10);

    std::cout << "PULSED BEAM ADRESS IN MAIN: " << &pulsed_beam << std::endl;

    Propagator<Gauss<LiF>> propagator(
            args,
            pulsed_beam,
            1,
            1e-5,
//            std::abs(pulsed_beam.z_diff / 500),
            10,
            100
            );

    propagator.propagate();


    return 0;
}
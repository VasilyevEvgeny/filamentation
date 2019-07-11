#include <iostream>
#include <omp.h>
#include <map>
#include <string>

#include "src/pulsed_beam/base_pulsed_beam/base_pulsed_beam.h"
#include "src/propagator.h"




std::map<std::string, std::string> parse_args(char **argv) {
     return  {{"global_root_dir", argv[1]},
              {"global_results_dir_name", argv[2]},
              {"python_interpreter", argv[3]},
              {"intensity_rt", argv[4]},
              {"track", argv[5]}};
}

int main(int argc, char** argv) {

    auto args = parse_args(argv);

    double lambda_0 = 1800e-9;

    Gauss<LiF> pulsed_beam(
            LiF(lambda_0),
            lambda_0,
//            1,
//            1,
            100e-6,
            512,
            40e-15,
            1024,
            5);

    Propagator<Gauss<LiF>> propagator(
            args,
            pulsed_beam,
            10,
            1e-4,
            1,
            4
            );

    propagator.propagate();




    return 0;
}
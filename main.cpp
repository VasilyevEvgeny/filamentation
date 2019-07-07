#include <iostream>
#include <omp.h>
#include <map>
#include <string>

#include "src/pulsed_beam/base_pulsed_beam/base_pulsed_beam.h"
#include "src/propagator.h"




std::map<std::string, std::string> parse_args(char **argv) {
     return  {{"global_root_dir", argv[1]},
              {"global_results_dir_name", argv[2]}};
}

int main(int argc, char** argv) {

    auto args = parse_args(argv);

    double lambda_0 = 1800e-9;

    Vortex<LiF> pulsed_beam(
            LiF(lambda_0),
            lambda_0,
            1,
            1,
            92e-6,
            1024,
            40e-15,
            1024,
            5);

    Propagator<Vortex<LiF>> propagator(
            args,
            pulsed_beam,
            10,
            1e-5
            );


    return 0;
}
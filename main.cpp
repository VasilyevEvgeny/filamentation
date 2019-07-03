#include <iostream>
#include <omp.h>
#include <map>
#include <string>

#include "src/PulsedBeam.h"
#include "src/Propagator.h"


std::map<std::string, std::string> parse_args(char **argv) {
     return  {{"global_root_dir", argv[1]},
              {"global_results_dir_name", argv[2]}};
}

int main(int argc, char** argv) {

    auto args = parse_args(argv);

    std::string medium_name = "LiF";
    PulsedBeam pulsed_beam(
            medium_name,
            1800e-9,
            1,
            1,
            100e-6,
            1024,
            500e-15,
            1024);

    pulsed_beam.initialize_field();

    Propagator propagator(
            args,
            pulsed_beam
            );


    return 0;
}
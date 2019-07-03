#include <iostream>
#include <omp.h>
#include <map>
#include <string>

#include "src/pulsed_beam.h"
#include "src/propagator.h"


std::map<std::string, std::string> parse_args(char **argv) {
     return  {{"global_root_dir", argv[1]},
              {"global_results_dir_name", argv[2]}};
}

int main(int argc, char** argv) {

    auto args = parse_args(argv);

    double lambda_0 = 1800e-9;

    SiO2 medium(lambda_0);
    PulsedBeam<SiO2> pulsed_beam(
            medium,
            lambda_0,
            1,
            1,
            100e-6,
            1024,
            500e-15,
            1024);

    pulsed_beam.initialize_field();

    Propagator<SiO2> propagator(
            args,
            pulsed_beam
            );


    return 0;
}
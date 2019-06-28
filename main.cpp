#include <iostream>
#include <omp.h>

#include "src/PulsedBeam.h"
#include "src/Propagator.h"

int main() {
    PulsedBeam pulsed_beam(
            1800e-9,
            1,
            1,
            100e-6,
            1024,
            500e-15,
            1024);

    pulsed_beam.initialize_field();
    std::cout << pulsed_beam.get_r_max() << std::endl;


    Propagator propagator(
            pulsed_beam);


    return 0;
}
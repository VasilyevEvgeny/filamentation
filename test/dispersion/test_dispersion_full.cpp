//
// Created by vasilyev on 24.07.2019.
//

#include "test_dispersion_full.h"

#include <chrono>
#include <thread>

#define base_test BaseTestDispersion<PulsedBeam<Medium>>

template<template<typename, typename...> class PulsedBeam, typename Medium>
TestDispersionFull<PulsedBeam<Medium>>::TestDispersionFull() = default;


template<template<typename, typename...> class PulsedBeam, typename Medium>
TestDispersionFull<PulsedBeam<Medium>>::TestDispersionFull(PulsedBeam<Medium>& _pulsed_beam) :
        base_test(_pulsed_beam) {



    auto args = base_test::initialize_args(base_test::term_name);

base_test::manager = Manager(args);
base_test::processor_dispersion = ProcessorDispersion(args, base_test::manager);

base_test::logger = Logger<PulsedBeam<Medium>, ProcessorDispersion>(args, base_test::pulsed_beam, base_test::manager,
base_test::processor_dispersion, base_test::track_info);
base_test::logger.save_initial_parameters_to_pdf(true, true);
base_test::logger.save_initial_parameters_to_yml();

    fourier_executor = FourierExecutor<PulsedBeam<Medium>>(base_test::pulsed_beam);
    dispersion_executor_full = DispersionExecutorFull<PulsedBeam<Medium>>(base_test::pulsed_beam);

}




template<template<typename, typename...> class PulsedBeam, typename Medium>
TestDispersionFull<PulsedBeam<Medium>>::~TestDispersionFull() = default;



template<template<typename, typename...> class PulsedBeam, typename Medium>
void TestDispersionFull<PulsedBeam<Medium>>::test() {

    auto t1 = std::chrono::high_resolution_clock::now();

    double z = 0.0;
    for (int step = 0; step < base_test::n_z + 1; ++step) {
        if (step) {

            fourier_executor.forward();

            dispersion_executor_full.process(base_test::dz);

            fourier_executor.backward();


            z += base_test::dz;
        }

        if (base_test::save_field_every) {
            if (!(step % base_test::save_field_every)) {
                base_test::logger.save_field(step);
            }
        }

        base::logger.flush_current_state(step, z);

        if (base::print_current_state_every) {
            if (!(step % base::print_current_state_every)) {
                base::logger.print_current_state(step, z);
            }
        }


    }

    auto t2 = std::chrono::high_resolution_clock::now();

    std::chrono::duration<float> fsec = t2 - t1;
    std::chrono::milliseconds d = std::chrono::duration_cast<std::chrono::milliseconds>(fsec);

    std::cout << fsec.count() << "s\n";

    base::logger.save_states_to_csv();
    base::logger.processor.go();
}


template class TestDispersionFull<Gauss<SiO2>>;
template class TestDispersionFull<Gauss<CaF2>>;
template class TestDispersionFull<Gauss<LiF>>;

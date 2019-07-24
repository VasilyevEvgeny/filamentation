//
// Created by vasilyev on 24.07.2019.
//

#include "test_dispersion_gvd.h"

#include <chrono>
#include <thread>

#define base BaseTestDispersion<PulsedBeam<Medium>>

template<template<typename, typename...> class PulsedBeam, typename Medium>
TestDispersionGVD<PulsedBeam<Medium>>::TestDispersionGVD() = default;


template<template<typename, typename...> class PulsedBeam, typename Medium>
TestDispersionGVD<PulsedBeam<Medium>>::TestDispersionGVD(PulsedBeam<Medium>& _pulsed_beam, std::string& _mode) :
    base(_pulsed_beam)
    , mode(_mode) {

    info = "gvd_" + mode;

    auto args = base::initialize_args(info);

    base::manager = Manager(args);
    base::processor_dispersion = ProcessorDispersion(args, base::manager);

    base::logger = Logger<PulsedBeam<Medium>, ProcessorDispersion>(args, base::pulsed_beam, base::manager,
    base::processor_dispersion, base::track_info);
    base::logger.save_initial_parameters_to_pdf(true, true);
    base::logger.save_initial_parameters_to_yml();

    fourier_executor = FourierExecutor<PulsedBeam<Medium>>(base::pulsed_beam);
    dispersion_executor_gvd = DispersionExecutorGVD<PulsedBeam<Medium>>(base::pulsed_beam, mode);

}


template<template<typename, typename...> class PulsedBeam, typename Medium>
TestDispersionGVD<PulsedBeam<Medium>>::~TestDispersionGVD() = default;





template<template<typename, typename...> class PulsedBeam, typename Medium>
void TestDispersionGVD<PulsedBeam<Medium>>::test() {

    auto t1 = std::chrono::high_resolution_clock::now();

    double z = 0.0;
    for (int step = 0; step < base::n_z + 1; ++step) {
        if (step) {



            if (mode == "fft") {
                fourier_executor.forward();
                dispersion_executor_gvd.process(base::dz);
                fourier_executor.backward();
            }
            else {
                dispersion_executor_gvd.process(base::dz);
            }



            z += base::dz;
        }

        if (base::save_field_every) {
            if (!(step % base::save_field_every)) {
                base::logger.save_field(step);
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

template class TestDispersionGVD<Gauss<SiO2>>;
template class TestDispersionGVD<Gauss<CaF2>>;
template class TestDispersionGVD<Gauss<LiF>>;
//
// Created by vasilyev on 17.07.2019.
//

#include <iostream>
#include <string>
#include <map>
#include <chrono>
#include <thread>

#include "test_diffraction.h"


template<template<typename, typename...> class PulsedBeam, typename Medium>
TestDiffraction<PulsedBeam<Medium>>::TestDiffraction(PulsedBeam<Medium>& _pulsed_beam) :
pulsed_beam(&_pulsed_beam) {

    auto args = initialize_args(pulsed_beam->info);

    n_z = 1000;

    save_field_every = 100;
    print_current_state_every = 10;

    dz = pulsed_beam->z_diff / n_z;
    track_info = {{"n_z", (double)(n_z + 1)},
                  {"dz", dz}};
    manager = Manager(args);
    processor_diffraction = ProcessorDiffraction(args, manager);

    logger = Logger<PulsedBeam<Medium>, ProcessorDiffraction>(args, pulsed_beam, manager,
                                                               processor_diffraction, track_info);
    logger.save_initial_parameters_to_pdf(true, true);
    logger.save_initial_parameters_to_yml();

    fourier_executor = FourierExecutor<PulsedBeam<Medium>>(pulsed_beam);
    diffraction_executor = DiffractionExecutor<PulsedBeam<Medium>>(pulsed_beam);
}

template<template<typename, typename...> class PulsedBeam, typename Medium>
std::map<std::string, std::string> TestDiffraction<PulsedBeam<Medium>>::initialize_args(std::string& info) {
    std::map<std::string, std::string> args = {
            {"prefix",                  "test_diffraction_" + info},
            {"path_to_project",         "C:/Users/vasilyev/Documents/CLion/filamentation"},
            {"global_root_dir",         "L:/Vasilyev"},
            {"global_results_dir_name", "Filamentation_results"},
            {"python_interpreter",      "C:/Users/vasilyev/Documents/venvs/filamentation/Scripts/python.exe"},
            {"intensity_rt",            "True"},
            {"track",                   "True"}};

    return args;
}
template<template<typename, typename...> class PulsedBeam, typename Medium>
void TestDiffraction<PulsedBeam<Medium>>::test() {

    auto t1 = std::chrono::high_resolution_clock::now();

    double z = 0.0;
    for (int step = 0; step < n_z + 1; ++step) {
        if (step) {

            fourier_executor.forward();

            diffraction_executor.process(dz);

            fourier_executor.backward();


            z += dz;
        }

        if (save_field_every) {
            if (!(step % save_field_every)) {
                logger.save_field(step);
            }
        }

        logger.flush_current_state(step, z);

        if (print_current_state_every) {
            if (!(step % print_current_state_every)) {
                logger.print_current_state(step, z);
            }
        }


    }

    auto t2 = std::chrono::high_resolution_clock::now();

    std::chrono::duration<float> fsec = t2 - t1;
    std::chrono::milliseconds d = std::chrono::duration_cast<std::chrono::milliseconds>(fsec);

    std::cout << fsec.count() << "s\n";

    logger.save_states_to_csv();
    logger.processor.go();
}

template<template<typename, typename...> class PulsedBeam, typename Medium>
TestDiffraction<PulsedBeam<Medium>>::~TestDiffraction() = default;


template class TestDiffraction<Gauss<SiO2>>;
template class TestDiffraction<Gauss<CaF2>>;
template class TestDiffraction<Gauss<LiF>>;
template class TestDiffraction<Vortex<SiO2>>;
template class TestDiffraction<Vortex<CaF2>>;
template class TestDiffraction<Vortex<LiF>>;

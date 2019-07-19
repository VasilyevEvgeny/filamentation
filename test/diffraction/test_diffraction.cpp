//
// Created by vasilyev on 17.07.2019.
//

#include <iostream>
#include <string>
#include <map>
#include <chrono>

#include "test_diffraction.h"


TestDiffraction::TestDiffraction() {

    std::map<std::string, std::string> args = {
            {"prefix", "test_diffraction"},
            {"path_to_project", "C:/Users/vasilyev/Documents/CLion/filamentation"},
            {"global_root_dir", "L:/Vasilyev"},
            {"global_results_dir_name", "Filamentation_results"},
            {"python_interpreter", "C:/Users/vasilyev/Documents/venvs/filamentation/Scripts/python.exe"},
            {"intensity_rt", "True"},
            {"track", "True"}};

    double lambda_0 = 1800e-9;

    medium = LiF(lambda_0);

    pulsed_beam = Gauss<LiF>(
            medium,
            lambda_0,
//            1,
//            1,
            100e-6,
            512,
            40e-15,
            1024,
            5);

    n_z = 100;
    dz = pulsed_beam.z_diff / n_z;
    track_info = {{"n_z", (double)(n_z + 1)},
                  {"dz", dz}};

    manager = Manager(args);
    processor_diffraction = ProcessorDiffraction(args, manager);

    logger = Logger<Gauss<LiF>, ProcessorDiffraction>(args, &pulsed_beam, manager, processor_diffraction, track_info);

    logger.save_initial_parameters_to_pdf(true, true);
    logger.save_initial_parameters_to_yml();

    save_field_every = 10;
    print_current_state_every = 10;


    fourier_executor = FourierExecutor<Gauss<LiF>>(&pulsed_beam);
    diffraction_executor = DiffractionExecutor<Gauss<LiF>>(&pulsed_beam);


}

void TestDiffraction::test() {

    auto t1 = std::chrono::high_resolution_clock::now();

    double z = 0.0;
    for (int step = 0; step < n_z + 1; ++step) {
        if (step) {

            /*
             * effects
             */

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


TestDiffraction::~TestDiffraction() = default;


template class Logger<Gauss<SiO2>, ProcessorDiffraction>;
template class Logger<Gauss<CaF2>, ProcessorDiffraction>;
template class Logger<Gauss<LiF>, ProcessorDiffraction>;
template class Logger<Ring<SiO2>, ProcessorDiffraction>;
template class Logger<Ring<CaF2>, ProcessorDiffraction>;
template class Logger<Ring<LiF>, ProcessorDiffraction>;
template class Logger<Vortex<SiO2>, ProcessorDiffraction>;
template class Logger<Vortex<CaF2>, ProcessorDiffraction>;
template class Logger<Vortex<LiF>, ProcessorDiffraction>;
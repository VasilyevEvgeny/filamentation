//
// Created by vasilyev on 28.06.2019.
//

#include <vector>
#include <omp.h>

#include "misc/misc.h"
#include "propagator.h"

Propagator::Propagator() = default;


Propagator::Propagator(ConfigManager& _config_manager,
                       std::shared_ptr<Postprocessor>& _postprocessor)
: config_manager(_config_manager)
, postprocessor(_postprocessor) {

    /*
     * dir manager
     */
    dir_manager = DirManager(config_manager);

    initialize();
}

Propagator::Propagator(ConfigManager& _config_manager,
                       std::shared_ptr<Postprocessor>& _postprocessor,
                       std::string& _multidir_name,
                       std::string& _current_results_dir_name)
        : config_manager(_config_manager)
        , postprocessor(_postprocessor) {

    /*
     * dir manager
     */
    dir_manager = DirManager(config_manager, _multidir_name, _current_results_dir_name);

    initialize();
}


Propagator::~Propagator() = default;

void Propagator::initialize() {
    /*
     * logger
     */
    logger = std::make_shared<Logger>(config_manager, dir_manager, config_manager.verbose);
    logger->add_propagation_event(std::string("creating propagator"));

    /*
     * threads
     */
    omp_set_num_threads(config_manager.num_threads);
    logger->add_propagation_event(std::string("number of threads: " + std::to_string(config_manager.num_threads)));

    /*
     * medium
     */
    if (config_manager.medium == "SiO2") {
        medium = std::make_shared<SiO2>(config_manager,
                                        logger);
    } else if (config_manager.medium == "CaF2") {
        medium = std::make_shared<CaF2>(config_manager,
                                        logger);
    } else {
        medium = std::make_shared<LiF>(config_manager,
                                       logger);
    }

    /*
     * pulsed_beam
     */
    if (config_manager.M == 0 && config_manager.m == 0) {
        pulsed_beam = std::make_shared<Gauss>(medium,
                                              config_manager,
                                              logger);
    } else if (config_manager.m == 0) {
        pulsed_beam = std::make_shared<Ring>(medium,
                                             config_manager,
                                             logger);
    } else {
        pulsed_beam = std::make_shared<Vortex>(medium,
                                               config_manager,
                                               logger);
    }

    /*
     * executor
     */
    linear_executor = std::make_shared<LinearExecutor>(pulsed_beam,
                                                       config_manager,
                                                       logger);
    nonlinear_executor = std::make_shared<NonlinearExecutor>(pulsed_beam,
                                                             config_manager,
                                                             logger);

    /*
     * saver
     */
    saver = Saver(pulsed_beam, linear_executor, nonlinear_executor, config_manager, dir_manager, logger);
    saver.save_initial_parameters_to_pdf(true, false);
    saver.save_initial_parameters_to_yml();

    dz = config_manager.dz_0;
    n_z = config_manager.n_z;
}


void Propagator::propagate() {

    logger->add_propagation_event(std::string("starting propagation!"));

    /*
     * Main cycle
     */

    double z = 0.0;
    size_t step;
    for (step = 0; step < n_z + 1; ++step) {
        if (step) {

            /*
             * effects
             */

            linear_executor->execute(dz);
            nonlinear_executor->execute(dz);

            z += dz;
        }

        if (config_manager.save_every) {
            if (!(step % config_manager.save_every)) {

                if (config_manager.save_field) {
                    auto t_start = TIME::now();
                    saver.save_field(step);
                    auto t_end = TIME::now();
                    logger->term_times["save_field"] += logger->duration(t_start, t_end);
                }

                if (config_manager.save_plasma) {
                    auto t_start = TIME::now();
                    saver.save_plasma(step);
                    auto t_end = TIME::now();
                    logger->term_times["save_plasma"] += logger->duration(t_start, t_end);
                }
            }
        }

        saver.flush_current_state(step, z, dz);

        if (config_manager.print_current_state_every) {
            if (!(step % config_manager.print_current_state_every)) {
                saver.print_current_state(step, z, dz);
            }
        }

        if (pulsed_beam->max_intensity(1) > config_manager.max_intensity_to_stop) {
            break;
        }
    }

    saver.save_states_to_csv(step);
    postprocessor->go(dir_manager, logger);

    logger->add_propagation_event(std::string("end\n"));
}

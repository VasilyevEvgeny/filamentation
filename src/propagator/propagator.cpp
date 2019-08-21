//
// Created by vasilyev on 28.06.2019.
//

#include <vector>

#include "misc/misc.h"
#include "propagator.h"

Propagator::Propagator() = default;


Propagator::Propagator(
        std::shared_ptr<BasePulsedBeam>& _pulsed_beam,
        ConfigManager& _config_manager,
        DirManager& _dir_manager,
        Postprocessor& _postprocessor,
        std::shared_ptr<Logger>& _logger)
: pulsed_beam(_pulsed_beam)
, config_manager(_config_manager)
, dir_manager(_dir_manager)
, postprocessor(_postprocessor)
, logger(_logger) {

    logger->add_propagation_event(std::string("creating propagator"));

    // executors
    linear_executor = std::make_shared<LinearExecutor>(pulsed_beam, config_manager, logger);
    nonlinear_executor = std::make_shared<NonlinearExecutor>(pulsed_beam, config_manager, logger);

    saver = Saver(pulsed_beam, linear_executor, nonlinear_executor, config_manager, dir_manager, postprocessor, logger);

    saver.save_initial_parameters_to_pdf(true, false);
    saver.save_initial_parameters_to_yml();
}


Propagator::~Propagator() = default;


void Propagator::propagate() {

    logger->add_propagation_event(std::string("starting propagation!\n"));

    /*
     * Main cycle
     */

    double z = 0.0;
    double dz = config_manager.dz_0;
    for (int step = 0; step < config_manager.n_z + 1; ++step) {
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
    }

    saver.save_states_to_csv();
    saver.postprocessor.go();

    logger->add_propagation_event(std::string("end"));
}

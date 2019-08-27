//
// Created by vasilyev on 30.06.2019.
//

#include <fstream>
#include <iomanip>

#include "saver.h"


Saver::Saver() = default;


Saver::Saver(std::shared_ptr<BasePulsedBeam>& _pulsed_beam,
             std::shared_ptr<LinearExecutor>& _linear_executor,
             std::shared_ptr<NonlinearExecutor>& _nonlinear_executor,
             ConfigManager& _config_manager,
             DirManager& _dir_manager,
             std::shared_ptr<Logger>& _logger)
: pulsed_beam(_pulsed_beam)
, linear_executor(_linear_executor)
, nonlinear_executor(_nonlinear_executor)
, config_manager(_config_manager)
, dir_manager(_dir_manager)
, logger(_logger) {

    logger->add_propagation_event(std::string("creating saver"));

    states_columns = {"step", "z, [m]", "dz, [m]", "I_max, [W/m^2]", "N_e_max, [m^-3]"};
    states = std::vector<std::vector<double>>(config_manager.n_z + 1,
            std::vector<double>(states_columns.size(), 0.0));

}

Saver::~Saver() {
    states.erase(states.begin(), states.end());
}


void Saver::print_current_state(size_t step, double z, double dz) {
    size_t w0 = 7;
    size_t w1 = 17;

    if (!step) {
        std::cout << std::setw(w0) << "step";
        std::cout << std::setw(w1) << "z, [m]";
        std::cout << std::setw(w1) << "dz, [m]";
        std::cout << std::setw(w1) << "I_max / I_0";
        std::cout << std::setw(w1) << "I_max, [W/m^2]";
        std::cout << std::setw(w1) << "N_e_max / N_0";
        std::cout << std::setw(w1) << "N_e_max, [m^-3]";
        std::cout << std::endl;
    }

    std::cout << std::setw(w0) << std::setfill('0') << std::fixed << std::setprecision(0) << step;
    std::cout << std::setw(w1) << std::setfill(' ') << std::scientific << std::setprecision(5) << z;
    std::cout << std::setw(w1) << std::setfill(' ') << std::scientific << std::setprecision(5) << dz;
    std::cout << std::setw(w1) << std::setfill(' ') << std::scientific << std::setprecision(5) << pulsed_beam->max_intensity(pulsed_beam->I_0);
    std::cout << std::setw(w1) << std::setfill(' ') << std::scientific << std::setprecision(5) << pulsed_beam->max_intensity(1);
    std::cout << std::setw(w1) << std::setfill(' ') << std::scientific << std::setprecision(5) << pulsed_beam->max_plasma(pulsed_beam->medium->N_0);
    std::cout << std::setw(w1) << std::setfill(' ') << std::scientific << std::setprecision(5) << pulsed_beam->max_plasma(1);
    std::cout << std::endl;
}


void Saver::flush_current_state(size_t step, double z, double dz) {
    states[step][0] = (double)step;
    states[step][1] = z;
    states[step][2] = dz;
    states[step][3] = pulsed_beam->max_intensity(1);
    states[step][4] = pulsed_beam->max_plasma(1);
}

void Saver::save_field(int step) {
    std::stringstream ss;
    ss << std::setw(5) << std::setfill('0') << step;
    std::string filename = dir_manager.field_dir + "/" + ss.str();

    std::ofstream f(filename);
    f << std::scientific;
    std::string space = "    ";
    for (int k = 0; k < pulsed_beam->n_r; ++k) {
        for (int s = 0; s < pulsed_beam->n_t; ++s) {
            if (s) {
                f << space;
            }
            f << pulsed_beam->field[k][s].real() << space << pulsed_beam->field[k][s].imag();
        }
        f << "\n";
    }

    f.close();
}

void Saver::save_plasma(int step) {
    std::stringstream ss;
    ss << std::setw(5) << std::setfill('0') << step;
    std::string filename = dir_manager.plasma_dir + "/" + ss.str();

    std::ofstream f(filename);
    f << std::scientific;
    std::string space = "    ";
    for (int k = 0; k < pulsed_beam->n_r; ++k) {
        for (int s = 0; s < pulsed_beam->n_t; ++s) {
            if (s) {
                f << space;
            }
            f << pulsed_beam->plasma[k][s];
        }
        f << "\n";
    }

    f.close();
}

void Saver::save_states_to_csv(size_t max_step) {

    logger->add_propagation_event(std::string("saving states to csv"));

    std::string filename = "propagation.csv";
    std::string path_to_save = dir_manager.current_results_dir + "/" + filename;
    std::ofstream f(path_to_save);

    size_t w0 = 7;
    size_t w1 = 20;
    std::string sep = "|";

    f << std::setw(w0) << std::setfill(' ') << states_columns[0] << sep;
    f << std::setw(w1) << std::setfill(' ') << states_columns[1] << sep;
    f << std::setw(w1) << std::setfill(' ') << states_columns[2] << sep;
    f << std::setw(w1) << std::setfill(' ') << states_columns[3] << sep;
    f << std::setw(w1) << std::setfill(' ') << states_columns[4] << std::endl;

    for (size_t step = 0; step < max_step; ++step) {
        f << std::setw(w0) << std::setfill('0') << std::fixed << std::setprecision(0) << states[step][0] << sep;
        f << std::setw(w1) << std::setfill(' ') << std::scientific << std::setprecision(5) << states[step][1] << sep;
        f << std::setw(w1) << std::setfill(' ') << std::scientific << std::setprecision(5) << states[step][2] << sep;
        f << std::setw(w1) << std::setfill(' ') << std::scientific << std::setprecision(5) << states[step][3] << sep;
        f << std::setw(w1) << std::setfill(' ') << std::scientific << std::setprecision(5) << states[step][4] << std::endl;
    }

    f.close();
}


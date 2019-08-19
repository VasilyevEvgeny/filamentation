//
// Created by vasilyev on 30.06.2019.
//

#include <fstream>
#include <iomanip>

#include "logger.h"

template<template<typename, typename...> class PulsedBeam, typename Medium, typename Postprocessor>
Logger<PulsedBeam<Medium>, Postprocessor>::Logger() = default;


template<template<typename, typename...> class PulsedBeam, typename Medium, typename Postprocessor>
Logger<PulsedBeam<Medium>, Postprocessor>::Logger(
        ConfigManager& _config_manager,
        DirManager& _dir_manager,
        Postprocessor& _postprocessor,
        std::shared_ptr<PulsedBeam<Medium>> _pulsed_beam,
        std::shared_ptr<LinearExecutor<PulsedBeam<Medium>>> _linear_executor,
        std::shared_ptr<NonlinearExecutor<PulsedBeam<Medium>>> _nonlinear_executor)
: config_manager(_config_manager)
, dir_manager(_dir_manager)
, postprocessor(_postprocessor)
, pulsed_beam(_pulsed_beam)
, linear_executor(_linear_executor)
, nonlinear_executor(_nonlinear_executor) {

    states_columns = {"step", "z, [m]", "h_z, [m]", "i_max, [W/m^2]"};
    states = std::vector<std::vector<double>>(config_manager.n_z + 1,
            std::vector<double>(states_columns.size(), 0.0));

}

template<template<typename, typename...> class PulsedBeam, typename Medium, typename Postprocessor>
Logger<PulsedBeam<Medium>, Postprocessor>::~Logger() {
    states.erase(states.begin(), states.end());
}

template<template<typename, typename...> class PulsedBeam, typename Medium, typename Postprocessor>
void Logger<PulsedBeam<Medium>, Postprocessor>::print_current_state(size_t step, double z, double dz) {
    size_t w1 = 7;
    size_t w2 = 20;
    size_t w3 = 20;
    size_t w4 = 20;
    size_t w5 = 20;

    if (!step) {
        std::cout << std::setw(w1) << "step";
        std::cout << std::setw(w2) << "z, [m]";
        std::cout << std::setw(w3) << "dz, [m]";
        std::cout << std::setw(w4) << "i_max / i_0";
        std::cout << std::setw(w5) << "i_max, [W/m^2]";
        std::cout << std::endl;
    }

    std::cout << std::setw(w1) << std::setfill('0') << std::fixed << std::setprecision(0) << step;
    std::cout << std::setw(w2) << std::setfill(' ') << std::scientific << std::setprecision(5) << z;
    std::cout << std::setw(w3) << std::setfill(' ') << std::scientific << std::setprecision(5) << dz;
    std::cout << std::setw(w4) << std::setfill(' ') << std::scientific << std::setprecision(5) << pulsed_beam->max_intensity(pulsed_beam->i_0);
    std::cout << std::setw(w5) << std::setfill(' ') << std::scientific << std::setprecision(5) << pulsed_beam->max_intensity(1);
    std::cout << std::endl;
}

template<template<typename, typename...> class PulsedBeam, typename Medium, typename Postprocessor>
void Logger<PulsedBeam<Medium>, Postprocessor>::flush_current_state(size_t step, double z, double dz) {
    states[step][0] = (double)step;
    states[step][1] = z;
    states[step][2] = dz;
    states[step][3] = pulsed_beam->max_intensity(1);
}


template<template<typename, typename...> class PulsedBeam, typename Medium, typename Postprocessor>
void Logger<PulsedBeam<Medium>, Postprocessor>::save_field(int step) {
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


template<template<typename, typename...> class PulsedBeam, typename Medium, typename Postprocessor>
void Logger<PulsedBeam<Medium>, Postprocessor>::save_plasma(int step) {
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


template<template<typename, typename...> class PulsedBeam, typename Medium, typename Postprocessor>
void Logger<PulsedBeam<Medium>, Postprocessor>::save_states_to_csv() {

    std::string filename = "propagation.csv";
    std::string path_to_save = dir_manager.current_results_dir + "/" + filename;
    std::ofstream f(path_to_save);

    size_t w1 = 7;
    size_t w2 = 20;
    size_t w3 = 20;
    size_t w4 = 20;
    std::string sep = "|";

    f << std::setw(w1) << std::setfill(' ') << states_columns[0] << sep;
    f << std::setw(w2) << std::setfill(' ') << states_columns[1] << sep;
    f << std::setw(w3) << std::setfill(' ') << states_columns[2] << sep;
    f << std::setw(w4) << std::setfill(' ') << states_columns[3] << std::endl;


    for (size_t step = 0; step < config_manager.n_z + 1; ++step) {
        f << std::setw(w1) << std::setfill('0') << std::fixed << std::setprecision(0) << states[step][0] << sep;
        f << std::setw(w2) << std::setfill(' ') << std::scientific << std::setprecision(5) << states[step][1] << sep;
        f << std::setw(w3) << std::setfill(' ') << std::scientific << std::setprecision(5) << states[step][2] << sep;
        f << std::setw(w4) << std::setfill(' ') << std::scientific << std::setprecision(5) << states[step][3] << std::endl;
    }

    f.close();
}

template class Logger<Gauss<SiO2>, Postprocessor>;
template class Logger<Gauss<CaF2>, Postprocessor>;
template class Logger<Gauss<LiF>, Postprocessor>;
template class Logger<Ring<SiO2>, Postprocessor>;
template class Logger<Ring<CaF2>, Postprocessor>;
template class Logger<Ring<LiF>, Postprocessor>;
template class Logger<Vortex<SiO2>, Postprocessor>;
template class Logger<Vortex<CaF2>, Postprocessor>;
template class Logger<Vortex<LiF>, Postprocessor>;

template class Logger<Gauss<SiO2>, ProcessorDiffraction>;
template class Logger<Gauss<CaF2>, ProcessorDiffraction>;
template class Logger<Gauss<LiF>, ProcessorDiffraction>;
template class Logger<Ring<SiO2>, ProcessorDiffraction>;
template class Logger<Ring<CaF2>, ProcessorDiffraction>;
template class Logger<Ring<LiF>, ProcessorDiffraction>;
template class Logger<Vortex<SiO2>, ProcessorDiffraction>;
template class Logger<Vortex<CaF2>, ProcessorDiffraction>;
template class Logger<Vortex<LiF>, ProcessorDiffraction>;

template class Logger<Gauss<SiO2>, ProcessorDispersion>;
template class Logger<Gauss<CaF2>, ProcessorDispersion>;
template class Logger<Gauss<LiF>, ProcessorDispersion>;
template class Logger<Ring<SiO2>, ProcessorDispersion>;
template class Logger<Ring<CaF2>, ProcessorDispersion>;
template class Logger<Ring<LiF>, ProcessorDispersion>;
template class Logger<Vortex<SiO2>, ProcessorDispersion>;
template class Logger<Vortex<CaF2>, ProcessorDispersion>;
template class Logger<Vortex<LiF>, ProcessorDispersion>;

template class Logger<BasePulsedBeam<BaseMedium>, Postprocessor>;
template class Logger<BasePulsedBeam<BaseMedium>, ProcessorDiffraction>;
template class Logger<BasePulsedBeam<BaseMedium>, ProcessorDispersion>;
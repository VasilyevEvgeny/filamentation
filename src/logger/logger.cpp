//
// Created by vasilyev on 30.06.2019.
//

#include <fstream>
#include <iomanip>

#include "logger.h"

template<template<typename, typename...> class PulsedBeam, typename Medium>
Logger<PulsedBeam<Medium>>::Logger() = default;


template<template<typename, typename...> class PulsedBeam, typename Medium>
Logger<PulsedBeam<Medium>>::Logger(
        std::map<std::string, std::string>& _args,
        PulsedBeam<Medium>& _pulsed_beam,
        std::map<std::string, double>& _track_info) :
    pulsed_beam(_pulsed_beam)
  , track_info(_track_info) {

    manager = Manager(_args);

    states_columns = {"step", "z, [m]", "h_z, [m]", "i_max, [W/m^2]"};
    states = std::vector<std::vector<double>>(track_info["n_z"],
            std::vector<double>(states_columns.size(), 0.0));

}

template<template<typename, typename...> class PulsedBeam, typename Medium>
Logger<PulsedBeam<Medium>>::~Logger() = default;


template<template<typename, typename...> class PulsedBeam, typename Medium>
void Logger<PulsedBeam<Medium>>::print_current_state(size_t step, double z) {
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
        std::cout << std::setw(w5) << "i_max, [TW/m^2]";
        std::cout << std::endl;
    }

    std::cout << std::setw(w1) << std::setfill('0') << std::fixed << std::setprecision(0) << step;
    std::cout << std::setw(w2) << std::setfill(' ') << std::scientific << std::setprecision(5) << z;
    std::cout << std::setw(w3) << std::setfill(' ') << std::scientific << std::setprecision(5) << track_info["dz"];
    std::cout << std::setw(w4) << std::setfill(' ') << std::scientific << std::setprecision(5) << pulsed_beam.max_intensity(pulsed_beam.i_0);
    std::cout << std::setw(w5) << std::setfill(' ') << std::scientific << std::setprecision(5) << pulsed_beam.max_intensity(1e16);
    std::cout << std::endl;
}

template<template<typename, typename...> class PulsedBeam, typename Medium>
void Logger<PulsedBeam<Medium>>::flush_current_state(size_t step, double z) {
    states[step][0] = (double)step;
    states[step][1] = z;
    states[step][2] = track_info["dz"];
    states[step][3] = pulsed_beam.max_intensity(1);
}


template<template<typename, typename...> class PulsedBeam, typename Medium>
void Logger<PulsedBeam<Medium>>::save_field(int step) {
    std::stringstream ss;
    ss << std::setw(5) << std::setfill('0') << step;
    std::string filename = manager.field_dir + "/" + ss.str();

    std::ofstream f(filename);
    f << std::scientific;
    std::string space = "    ";
    for (int k = 0; k < pulsed_beam.n_r; ++k) {
        for (int s = 0; s < pulsed_beam.n_t; ++s) {
            if (s) {
                f << space;
            }
            f << pulsed_beam.field[k][s].real() << space << pulsed_beam.field[k][s].imag();
        }
        f << "\n";
    }

    f.close();
}

template<template<typename, typename...> class PulsedBeam, typename Medium>
void Logger<PulsedBeam<Medium>>::save_states_to_csv() {

    std::string filename = "propagation.csv";
    std::string path_to_save = manager.current_results_dir + "/" + filename;
    std::ofstream f(path_to_save);

    size_t w1 = 7;
    size_t w2 = 20;
    size_t w3 = 20;
    size_t w4 = 20;

    f << std::setw(w1) << std::setfill(' ') << states_columns[0];
    f << std::setw(w2) << std::setfill(' ') << states_columns[1];
    f << std::setw(w3) << std::setfill(' ') << states_columns[2];
    f << std::setw(w4) << std::setfill(' ') << states_columns[3];

    f << "\n";

    for (size_t step = 0; step < track_info["n_z"]; ++step) {
        f << std::setw(w1) << std::setfill('0') << std::fixed << std::setprecision(0) << states[step][0];
        f << std::setw(w2) << std::setfill(' ') << std::scientific << std::setprecision(5) << states[step][1];
        f << std::setw(w3) << std::setfill(' ') << std::scientific << std::setprecision(5) << states[step][2];
        f << std::setw(w4) << std::setfill(' ') << std::scientific << std::setprecision(5) << states[step][3] << std::endl;
    }

    f.close();
}

template class Logger<Gauss<SiO2>>;
template class Logger<Gauss<CaF2>>;
template class Logger<Gauss<LiF>>;
template class Logger<Ring<SiO2>>;
template class Logger<Ring<CaF2>>;
template class Logger<Ring<LiF>>;
template class Logger<Vortex<SiO2>>;
template class Logger<Vortex<CaF2>>;
template class Logger<Vortex<LiF>>;
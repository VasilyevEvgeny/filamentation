//
// Created by vasilyev on 24.07.2019.
//

#include "base_test_dispersion.h"

template<template<typename, typename...> class PulsedBeam, typename Medium>
BaseTestDispersion<PulsedBeam<Medium>>::BaseTestDispersion() = default;


template<template<typename, typename...> class PulsedBeam, typename Medium>
BaseTestDispersion<PulsedBeam<Medium>>::BaseTestDispersion(PulsedBeam<Medium>& _pulsed_beam) :
        pulsed_beam(&_pulsed_beam) {



    n_z = 500;

    save_field_every = 100;
    print_current_state_every = 10;

    dz = std::abs(pulsed_beam->z_disp / n_z);
    track_info = {{"n_z", (double)(n_z + 1)},
                  {"dz", dz}};



}


template<template<typename, typename...> class PulsedBeam, typename Medium>
std::map<std::string, std::string> BaseTestDispersion<PulsedBeam<Medium>>::initialize_args(std::string& term_name) {
    std::map<std::string, std::string> args = {
            {"prefix",                  "test_" + term_name},
            {"path_to_project",         "C:/Users/vasilyev/Documents/CLion/filamentation"},
            {"global_root_dir",         "L:/Vasilyev"},
            {"global_results_dir_name", "Filamentation_results"},
            {"python_interpreter",      "C:/Users/vasilyev/Documents/venvs/filamentation/Scripts/python.exe"},
            {"intensity_rt",            "True"},
            {"track",                   "True"}};

    return args;
}


template<template<typename, typename...> class PulsedBeam, typename Medium>
BaseTestDispersion<PulsedBeam<Medium>>::~BaseTestDispersion() = default;


template class BaseTestDispersion<Gauss<SiO2>>;
template class BaseTestDispersion<Gauss<CaF2>>;
template class BaseTestDispersion<Gauss<LiF>>;

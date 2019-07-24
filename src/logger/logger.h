//
// Created by vasilyev on 30.06.2019.
//

#ifndef FILAMENTATION_LOGGER_H
#define FILAMENTATION_LOGGER_H

#include <map>
#include <vector>

#include "../pulsed_beam/gauss.h"
#include "../pulsed_beam/ring.h"
#include "../pulsed_beam/vortex.h"
#include "../manager.h"
#include "../processor.h"

#include "diffraction/processor_diffraction.h"
#include "dispersion/processor_dispersion.h"

template<typename PB, typename P> class Logger;

template<template<typename, typename...> class PulsedBeam, typename Medium, typename Processor>
class Logger<PulsedBeam<Medium>, Processor> {
public:
    Logger();
    explicit Logger(
            std::map<std::string, std::string>& _args,
            PulsedBeam<Medium>* _pulsed_beam,
            Manager& _manager,
            Processor& _processor,
            std::map<std::string, double>& _track_info);
    ~Logger();

    Manager manager;
    Processor processor;

    PulsedBeam<Medium>* pulsed_beam;
    std::map<std::string, double> track_info;

    std::vector<std::string> states_columns;
    std::vector<std::vector<double>> states;

    void add_start(std::string& tex_file_data);
    void add_end(std::string& tex_file_data);
    void add_to_tex_file_data(std::string& tex_file_data, std::string& str, std::vector<size_t>& params);
    void add_to_tex_file_data(std::string& tex_file_data, std::string& str, std::vector<double>& params);
    void add_to_tex_file_data(std::string& tex_file_data, std::string& str, std::vector<std::string>& params);
    void add_to_yml_file_data(std::string& tex_file_data, std::string& str, std::vector<double>& params);
    void add_to_yml_file_data(std::string& tex_file_data, std::string& str, std::vector<std::string>& params);

    void save_initial_parameters_to_pdf(bool delete_tmp_files, bool delete_tex_file);
    void save_initial_parameters_to_yml();

    void print_current_state(size_t step, double z);
    void flush_current_state(size_t step, double z);
    void save_states_to_csv();
    void save_field(int step);

private:

};






#endif //FILAMENTATION_LOGGER_H



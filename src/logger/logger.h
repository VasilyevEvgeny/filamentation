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
#include "manager/dir_manager.h"
#include "manager/config_manager.h"
#include "../processor.h"
#include "term/wave_equation/linear/base_linear_term.h"
#include "term/wave_equation/nonlinear/base_nonlinear_term.h"
#include "term/kinetic_equation/kinetic_equation.h"

#include "diffraction/processor_diffraction.h"
#include "dispersion/processor_dispersion.h"

template<typename PB, typename P> class Logger;

template<template<typename, typename...> class PulsedBeam, typename Medium, typename Processor>
class Logger<PulsedBeam<Medium>, Processor> {
public:
    Logger();
    explicit Logger(
            ConfigManager& _config_manager,
            DirManager& _dir_manager,
            Processor& _processor,
            PulsedBeam<Medium>* _pulsed_beam,
            std::map<std::string, BaseLinearTerm<PulsedBeam<Medium>>*>& _linear_terms_pool,
            std::map<std::string, BaseNonlinearTerm<PulsedBeam<Medium>>*>& _nonlinear_terms_pool,
            std::vector<std::string>& _active_linear_terms,
            std::vector<std::string>& _active_nonlinear_terms,
            KineticEquation<PulsedBeam<Medium>>& _kinetic_equation);
    ~Logger();

    ConfigManager config_manager;
    DirManager dir_manager;
    Processor processor;

    PulsedBeam<Medium>* pulsed_beam;

    std::vector<std::string> states_columns;
    std::vector<std::vector<double>> states;

    std::map<std::string, BaseLinearTerm<PulsedBeam<Medium>>*> linear_terms_pool;
    std::map<std::string, BaseNonlinearTerm<PulsedBeam<Medium>>*> nonlinear_terms_pool;
    std::vector<std::string> active_linear_terms;
    std::vector<std::string> active_nonlinear_terms;
    KineticEquation<PulsedBeam<Medium>> kinetic_equation;

    void add_start(std::string& tex_file_data);
    void add_end(std::string& tex_file_data);
    void add_to_tex_file_data(std::string& tex_file_data, std::string& str, std::vector<size_t>& params);
    void add_to_tex_file_data(std::string& tex_file_data, std::string& str, std::vector<double>& params);
    void add_to_tex_file_data(std::string& tex_file_data, std::string& str, std::vector<std::string>& params);
    void add_to_yml_file_data(std::string& tex_file_data, std::string& str, std::vector<double>& params);
    void add_to_yml_file_data(std::string& tex_file_data, std::string& str, std::vector<std::string>& params);

    void save_initial_parameters_to_pdf(bool delete_tmp_files, bool delete_tex_file);
    void save_initial_parameters_to_yml();

    void print_current_state(size_t step, double z, double dz);
    void flush_current_state(size_t step, double z, double dz);
    void save_states_to_csv();
    void save_field(int step);
    void save_plasma(int step);

private:

};






#endif //FILAMENTATION_LOGGER_H



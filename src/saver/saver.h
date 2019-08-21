//
// Created by vasilyev on 30.06.2019.
//

#ifndef FILAMENTATION_SAVER_H
#define FILAMENTATION_SAVER_H

#include <map>
#include <vector>
#include <memory>

#include "pulsed_beam/gauss/gauss.h"
#include "pulsed_beam/ring/ring.h"
#include "pulsed_beam/vortex/vortex.h"
#include "manager/dir_manager/dir_manager.h"
#include "manager/config_manager/config_manager.h"
#include "postprocessor/postprocessor.h"
#include "term/wave_equation/linear/base_linear_term.h"
#include "term/wave_equation/nonlinear/base_nonlinear_term.h"
#include "term/kinetic_equation/kinetic_equation.h"
#include "executor/linear_executor/linear_executor.h"
#include "executor/nonlinear_executor/nonlinear_executor.h"


class Saver {
public:
    Saver();
    explicit Saver(std::shared_ptr<BasePulsedBeam>& _pulsed_beam,
                   std::shared_ptr<LinearExecutor>& _linear_executor,
                   std::shared_ptr<NonlinearExecutor>& _nonlinear_executor,
                   ConfigManager& _config_manager,
                   DirManager& _dir_manager,
                   //std::shared_ptr<Postprocessor>& _postprocessor,
                   std::shared_ptr<Logger>& _logger);
    ~Saver();

    std::shared_ptr<BasePulsedBeam> pulsed_beam;

    std::shared_ptr<LinearExecutor> linear_executor;
    std::shared_ptr<NonlinearExecutor> nonlinear_executor;

    ConfigManager config_manager;
    DirManager dir_manager;
    //std::shared_ptr<Postprocessor> postprocessor;
    std::shared_ptr<Logger> logger;

    std::vector<std::string> states_columns;
    std::vector<std::vector<double>> states;

    void add_start(std::string& tex_file_data) const;
    void add_end(std::string& tex_file_data) const;
    void add_to_tex_file_data(std::string& tex_file_data, std::string& str, std::vector<size_t>& params) const;
    void add_to_tex_file_data(std::string& tex_file_data, std::string& str, std::vector<double>& params) const;
    void add_to_tex_file_data(std::string& tex_file_data, std::string& str, std::vector<std::string>& params) const;
    void add_to_yml_file_data(std::string& tex_file_data, std::string& str, std::vector<double>& params) const;
    void add_to_yml_file_data(std::string& tex_file_data, std::string& str, std::vector<std::string>& params) const;

    void save_initial_parameters_to_pdf(bool delete_tmp_files, bool delete_tex_file);
    void save_initial_parameters_to_yml();

    void print_current_state(size_t step, double z, double dz);
    void flush_current_state(size_t step, double z, double dz);
    void save_states_to_csv();
    void save_field(int step);
    void save_plasma(int step);

private:

};






#endif //FILAMENTATION_SAVER_H



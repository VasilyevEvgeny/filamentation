//
// Created by vasilyev on 30.06.2019.
//

#ifndef FILAMENTATION_LOGGER_H
#define FILAMENTATION_LOGGER_H

#include "pulsed_beam.h"

template<typename Medium> class Logger {
public:
    explicit Logger(PulsedBeam<Medium>& _pulsed_beam);
    ~Logger();

    PulsedBeam<Medium> pulsed_beam;

    std::string tex_file_data;


    void add_start();
    void add_end();
    void add_to_tex_file_data(std::string& str, std::vector<size_t>& params);
    void add_to_tex_file_data(std::string& str, std::vector<double>& params);
    void add_to_tex_file_data(std::string& str, std::vector<std::string>& params);

    void save_initial_parameters(std::string& path, bool delete_tmp_files, bool delete_tex_file);

private:
};


#endif //FILAMENTATION_LOGGER_H

//
// Created by vasilyev on 30.06.2019.
//

#ifndef FILAMENTATION_LOGGER_H
#define FILAMENTATION_LOGGER_H

#include "PulsedBeam.h"

class Logger {
public:
    Logger();
    ~Logger();

    void save_initial_parameters(PulsedBeam& pulsed_beam, std::string& path,
            bool delete_tmp_files, bool delete_tex_file) const;

private:
};


#endif //FILAMENTATION_LOGGER_H

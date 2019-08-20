//
// Created by vasilyev on 10.07.2019.
//

#ifndef FILAMENTATION_PROCESSOR_H
#define FILAMENTATION_PROCESSOR_H

#include <string>
#include <map>
#include <memory>

#include "logger/logger.h"
#include "manager/config_manager/config_manager.h"
#include "manager/dir_manager/dir_manager.h"


class Postprocessor {
public:
    Postprocessor();
    explicit Postprocessor(
            ConfigManager& _config_manager,
            DirManager& _dir_manager,
            std::shared_ptr<Logger>& _logger);

    ~Postprocessor();

    DirManager dir_manager;
    std::shared_ptr<Logger> logger;

    std::string path_to_project;
    std::string path_to_python_interpreter;

    bool plot_intensity_rt;
    bool plot_plasma_rt;
    bool plot_track;

    virtual void go();
};


#endif //FILAMENTATION_PROCESSOR_H

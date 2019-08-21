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
    explicit Postprocessor(ConfigManager& _config_manager);

    ~Postprocessor();

    std::string path_to_project;
    std::string path_to_python_interpreter;

    bool plot_intensity_rt;
    bool plot_plasma_rt;
    bool plot_track;

    virtual void go(DirManager& dir_manager, std::shared_ptr<Logger>& logger);
    void postprocess(DirManager& dir_manager,
                     std::shared_ptr<Logger>& logger,
                     const std::string& module,
                     const std::string& path_to_script,
                     const std::string& log_info);
};


#endif //FILAMENTATION_PROCESSOR_H

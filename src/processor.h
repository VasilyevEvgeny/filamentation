//
// Created by vasilyev on 10.07.2019.
//

#ifndef FILAMENTATION_PROCESSOR_H
#define FILAMENTATION_PROCESSOR_H

#include <string>
#include <map>

#include "manager/config_manager.h"
#include "manager/dir_manager.h"


class Processor {
public:
    Processor();
    explicit Processor(
            ConfigManager& config_manager,
            DirManager& _manager);

    std::string path_to_project;
    std::string path_to_python_interpreter;

    bool plot_intensity_rt;
    bool plot_plasma_rt;
    bool plot_track;

    DirManager manager;

    virtual void go();
};


#endif //FILAMENTATION_PROCESSOR_H

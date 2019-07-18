//
// Created by vasilyev on 10.07.2019.
//

#ifndef FILAMENTATION_PROCESSOR_H
#define FILAMENTATION_PROCESSOR_H

#include <string>
#include <map>

#include "manager.h"


class Processor {
public:
    Processor();
    explicit Processor(std::map<std::string, std::string>& _args, Manager& _manager);

    std::string path_to_project;
    std::string path_to_python_interpreter;
    std::string intensity_rt;
    std::string track;

    Manager manager;

    std::string get_cwd();
    void go();
};


#endif //FILAMENTATION_PROCESSOR_H

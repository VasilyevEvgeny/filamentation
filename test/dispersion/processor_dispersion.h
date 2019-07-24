//
// Created by vasilyev on 24.07.2019.
//

#ifndef FILAMENTATION_PROCESSORDISPERSION_H
#define FILAMENTATION_PROCESSORDISPERSION_H

#include "processor.h"

class ProcessorDispersion : public Processor {
public:
    ProcessorDispersion();
    ProcessorDispersion(std::map<std::string, std::string>& args, Manager& _manager);

    std::string path_to_test_script;

    void go() override;

    ~ProcessorDispersion();
};


#endif //FILAMENTATION_PROCESSORDISPERSION_H

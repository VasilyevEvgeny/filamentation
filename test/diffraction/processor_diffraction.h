//
// Created by vasilyev on 18.07.2019.
//

#ifndef FILAMENTATION_PROCESSORDIFFRACTION_H
#define FILAMENTATION_PROCESSORDIFFRACTION_H

#include "processor.h"

class ProcessorDiffraction : public Processor {
public:
    ProcessorDiffraction();
    ProcessorDiffraction(std::map<std::string, std::string>& args, Manager& _manager);

    std::string path_to_test_script;

    void go() override;

    ~ProcessorDiffraction();
};


#endif //FILAMENTATION_PROCESSORDIFFRACTION_H

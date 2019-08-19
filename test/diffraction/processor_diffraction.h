//
// Created by vasilyev on 18.07.2019.
//

#ifndef FILAMENTATION_PROCESSORDIFFRACTION_H
#define FILAMENTATION_PROCESSORDIFFRACTION_H

#include "logger/postprocessor/postprocessor.h"
#include "manager/config_manager/config_manager.h"

class ProcessorDiffraction : public Postprocessor {
public:
    ProcessorDiffraction();
    ProcessorDiffraction(ConfigManager& _config_manager, DirManager& _dir_manager);

    std::string path_to_test_script;

    void go() override;

    ~ProcessorDiffraction();
};


#endif //FILAMENTATION_PROCESSORDIFFRACTION_H

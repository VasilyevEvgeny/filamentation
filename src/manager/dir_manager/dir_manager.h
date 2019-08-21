//
// Created by vasilyev on 29.06.2019.
//

#ifndef FILAMENTATION_DIRMANAGER_H
#define FILAMENTATION_DIRMANAGER_H

#include <direct.h>
#include <string>
#include <map>
#include <iostream>

#include "manager/config_manager/config_manager.h"

class DirManager {
public:
    DirManager() = default;
    explicit DirManager(ConfigManager& config_manager);
    explicit DirManager(ConfigManager& config_manager, std::string& multidir_name, std::string& _current_results_dir_name);
    ~DirManager();

    std::string global_results_dir;
    std::string ionization_tables_dir;

    std::string current_results_dir_name;
    std::string current_results_dir;

    std::string field_dir_name;
    std::string field_dir;

    std::string plasma_dir_name;
    std::string plasma_dir;

    std::string get_current_datetime() const;

    void initialize(ConfigManager& config_manager);

};


#endif //FILAMENTATION_DIRMANAGER_H

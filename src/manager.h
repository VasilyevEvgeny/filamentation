//
// Created by vasilyev on 29.06.2019.
//

#ifndef FILAMENTATION_MANAGER_H
#define FILAMENTATION_MANAGER_H

#include <direct.h>
#include <string>
#include <map>
#include <iostream>

class Manager {
public:
    Manager() = default;
    explicit Manager(std::map<std::string, std::string>& args);
    ~Manager();

    std::string global_results_dir;
    std::string ionization_tables_dir;

    std::string current_results_dir_name;
    std::string current_results_dir;

    std::string field_dir_name;
    std::string field_dir;

    std::string plasma_dir_name;
    std::string plasma_dir;

private:
    std::string get_current_datetime() const;
};


#endif //FILAMENTATION_MANAGER_H

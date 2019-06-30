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
    explicit Manager(std::map<std::string, std::string>& args);
    ~Manager();

private:
    std::string get_current_datetime() const;
};


#endif //FILAMENTATION_MANAGER_H

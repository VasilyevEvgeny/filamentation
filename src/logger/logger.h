//
// Created by vasilyev on 19.08.2019.
//

#ifndef FILAMENTATION_LOGGER_H
#define FILAMENTATION_LOGGER_H

#include <string>
#include <fstream>

#include "manager/dir_manager/dir_manager.h"

class Logger {
public:
    Logger();
    explicit Logger(DirManager& _dir_manager, bool _verbose);
    ~Logger();

    bool verbose;

    std::string propagation_log_filename;
    std::ofstream propagation_log_handler;
    void add_propagation_event(const std::string& event_info);

    std::string time_log_filename;
    std::ofstream time_log_handler;

    std::string get_current_datetime() const;
};


#endif //FILAMENTATION_LOGGER_H

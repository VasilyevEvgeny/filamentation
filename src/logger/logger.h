//
// Created by vasilyev on 19.08.2019.
//

#ifndef FILAMENTATION_LOGGER_H
#define FILAMENTATION_LOGGER_H

#include <string>
#include <fstream>
#include <chrono>

#include "manager/dir_manager/dir_manager.h"
#include "manager/config_manager/config_manager.h"

class Logger {
public:
    Logger();
    explicit Logger(ConfigManager& _config_manager,
                    DirManager& _dir_manager,
                    bool _verbose);
    ~Logger();

    std::map<std::string, double> term_times;

    bool verbose;

    std::string propagation_log_filename;
    std::ofstream propagation_log_handler;
    void add_propagation_event(const std::string& event_info);

    std::string time_log_filename;
    std::ofstream time_log_handler;

    double duration(std::chrono::time_point<std::chrono::high_resolution_clock> t_start,
                    std::chrono::time_point<std::chrono::high_resolution_clock> t_end) const;

    std::string convert_seconds_to_time_string(double seconds);
    void make_time_log();

};


#endif //FILAMENTATION_LOGGER_H

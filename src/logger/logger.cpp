//
// Created by vasilyev on 19.08.2019.
//

#include <ctime>
#include <fstream>

#include "logger.h"

Logger::Logger() = default;

Logger::Logger(DirManager& _dir_manager, bool _verbose)
: verbose(_verbose) {

    try {

        // propagation.log

        propagation_log_filename = "propagation";
        std::string propagation_log_path = _dir_manager.current_results_dir + "/" + propagation_log_filename + ".log";

        propagation_log_handler = std::ofstream(propagation_log_path);
        if (!propagation_log_handler.is_open()) {
            throw std::runtime_error("propagation.log wasn't created!");
        }


        // time.log

        time_log_filename = "time";
        std::string time_log_path = _dir_manager.current_results_dir + "/" + time_log_filename + ".log";
        time_log_handler = std::ofstream(time_log_path);
        if (!time_log_handler.is_open()) {
            throw std::runtime_error("time.log wasn't created!");
        }
    }
    catch (std::runtime_error &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        exit(-1);
    }

}



Logger::~Logger() {
    propagation_log_handler.close();
    time_log_handler.close();

}

void Logger::add_propagation_event(const std::string& event_info) {

    std::string log_string = get_current_datetime() + " " + event_info + "\n";

    propagation_log_handler << log_string;
    propagation_log_handler.flush();

    if (verbose) {
        std::cout << log_string;
    }

}

std::string Logger::get_current_datetime() const {
    time_t rawtime;
    struct tm *timeinfo;
    char buffer[80];

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer,sizeof(buffer),"[%Y-%m-%d %H:%M:%S]", timeinfo);

    return std::string(buffer);
}


//
// Created by vasilyev on 19.08.2019.
//

#include <ctime>
#include <fstream>
#include <sstream>
#include <iomanip>

#include "logger.h"

Logger::Logger() = default;

Logger::Logger(ConfigManager& _config_manager,
               DirManager& _dir_manager,
               bool _verbose)
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

void Logger::make_time_log() {

    time_log_handler << std::setw(30) << std::setfill(' ');
    time_log_handler << "MODULE";
    time_log_handler << std::setw(30) << std::setfill(' ');
    time_log_handler << "TIME" << std::endl;

    for (auto& item : term_times) {
        time_log_handler << std::setw(30) << std::setfill(' ');
        time_log_handler << item.first;
        time_log_handler << std::setw(30) << std::setfill(' ');
        time_log_handler << convert_seconds_to_time_string(item.second) << std::endl;
    }
}

Logger::~Logger() {

    make_time_log();

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

double Logger::duration(std::chrono::time_point<std::chrono::high_resolution_clock> t_start,
                std::chrono::time_point<std::chrono::high_resolution_clock> t_end) const {
    std::chrono::duration<double> duration = t_end - t_start;
    std::chrono::milliseconds d = std::chrono::duration_cast<std::chrono::milliseconds>(duration);

    return d.count() / 1e3;
}


std::string Logger::convert_seconds_to_time_string(const double seconds) {
    auto etc = (size_t)((seconds - (size_t)seconds) * 1e2);
    auto time = (size_t)seconds;

    auto secs = time % 60;
    time /= 60;

    auto mins = time % 60;
    time /= 60;

    auto hours = time % 24;
    auto days = time / 24;

    std::string time_string;
    std::ostringstream ss(time_string);
    ss << std::setw(2) << std::setfill('0');
    ss << days << " d  ";
    ss << std::setw(2) << std::setfill('0');
    ss << hours << " h  ";
    ss << std::setw(2) << std::setfill('0');
    ss << mins << " m  ";
    ss << std::setw(2) << std::setfill('0');
    ss << secs << ".";
    ss << std::setw(2) << std::setfill('0');
    ss << etc << " s";

    return ss.str();

}

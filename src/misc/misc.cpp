//
// Created by vasilyev on 22.07.2019.
//

#include <random>
#include <map>


#include "misc.h"
#include <ctime>



int generate_random_number(int min, int max) {
    std::random_device rd;     // only used once to initialise (seed) engine
    std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
    std::uniform_int_distribution<int> uni(min,max); // guaranteed unbiased

    return uni(rng);
}

std::string get_current_datetime(const std::string& mode) {
    try {
        if (mode != "logger" && mode != "dir_manager") {
            throw std::runtime_error("Wrong mode!");
        }
    }
    catch (std::runtime_error &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    time_t rawtime;
    struct tm *timeinfo;
    char buffer[80];

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    if (mode == "logger") {
        strftime(buffer,sizeof(buffer),"[%Y-%m-%d %H:%M:%S]", timeinfo);
    }
    else {
        strftime(buffer,sizeof(buffer),"%Y-%m-%d_%H-%M-%S", timeinfo);
    }

    return std::string(buffer);
}
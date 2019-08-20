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


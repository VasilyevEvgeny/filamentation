//
// Created by vasilyev on 29.07.2019.
//

#include "smoothed_keldysh.h"

#include <iostream>


SmoothedKeldysh::SmoothedKeldysh() = default;


SmoothedKeldysh::SmoothedKeldysh(
        double _omega_0,
        double _U_i,
        double _N_0,
        double _n_0,
        std::shared_ptr<Logger>& _logger)
        : BaseKeldysh(_omega_0,
                      _U_i,
                      _N_0,
                      _n_0,
                      _logger) {
    name = "smoothed";

}


SmoothedKeldysh::~SmoothedKeldysh() = default;



double SmoothedKeldysh::calculate_x_plus_1(double x) {
    return x + 1;
}
//
// Created by vasilyev on 29.07.2019.
//

#include "original_keldysh.h"


OriginalKeldysh::OriginalKeldysh() = default;


OriginalKeldysh::OriginalKeldysh(
        double _omega_0,
        double _U_i,
        double _N_0,
        double _n_0)
: BaseKeldysh(_omega_0,
              _U_i,
              _N_0,
              _n_0) {

}


OriginalKeldysh::~OriginalKeldysh() = default;



double OriginalKeldysh::calculate_x_plus_1(double x) {
    return int(x + 1);
}
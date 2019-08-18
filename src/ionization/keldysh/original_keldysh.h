//
// Created by vasilyev on 29.07.2019.
//

#ifndef FILAMENTATION_ORIGINALKELDYSHIONIZATION_H
#define FILAMENTATION_ORIGINALKELDYSHIONIZATION_H

#include "base_keldysh.h"

class OriginalKeldysh : public BaseKeldysh {
public:
    OriginalKeldysh();
    explicit OriginalKeldysh(double _omega_0,
                             double _U_i,
                             double _N_0,
                             double _n_0);
    ~OriginalKeldysh() override;

    double calculate_x_plus_1(double x) override;

};


#endif //FILAMENTATION_ORIGINALKELDYSHIONIZATION_H

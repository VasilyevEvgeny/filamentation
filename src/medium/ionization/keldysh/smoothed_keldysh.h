//
// Created by vasilyev on 29.07.2019.
//

#ifndef FILAMENTATION_SMOOTHEDKELDYSHIONIZATION_H
#define FILAMENTATION_SMOOTHEDKELDYSHIONIZATION_H

#include "base_keldysh.h"

class SmoothedKeldysh : public BaseKeldysh {
public:
    SmoothedKeldysh();
    explicit SmoothedKeldysh(MathConstants& _math_constants,
                             double _omega_0,
                             double _U_i,
                             double _N_0,
                             double _n_0);
    ~SmoothedKeldysh() override;

    double calculate_x_plus_1(double x) override;

};


#endif //FILAMENTATION_SMOOTHEDKELDYSHIONIZATION_H

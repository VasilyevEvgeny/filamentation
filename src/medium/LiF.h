//
// Created by vasilyev on 02.07.2019.
//

#ifndef FILAMENTATION_LIF_H
#define FILAMENTATION_LIF_H

#include "medium.h"

class LiF : public Medium {
public:
    explicit LiF(double _lambda_0);
    ~LiF() override;

    void initialize_kerr_parameters() override;
    void initialize_ionization_parameters() override;

private:


};

#endif //FILAMENTATION_LIF_H

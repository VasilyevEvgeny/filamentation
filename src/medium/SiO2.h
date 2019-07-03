//
// Created by vasilyev on 02.07.2019.
//

#ifndef FILAMENTATION_SIO2_H
#define FILAMENTATION_SIO2_H

#include "medium.h"

class SiO2 : public Medium {
public:
    explicit SiO2(double _lambda_0);
    ~SiO2() override;

    void initialize_kerr_parameters() override;
    void initialize_ionization_parameters() override;

private:


};


#endif //FILAMENTATION_SIO2_H

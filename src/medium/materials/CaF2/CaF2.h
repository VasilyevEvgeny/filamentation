//
// Created by vasilyev on 02.07.2019.
//

#ifndef FILAMENTATION_CAF2_H
#define FILAMENTATION_CAF2_H

#include "medium/materials/base_medium.h"

class CaF2 : public BaseMedium {
public:
    CaF2();
    explicit CaF2(double _lambda_0);
    ~CaF2() override;

    void initialize_kerr_parameters() override;
    void initialize_ionization_parameters() override;

private:


};


#endif //FILAMENTATION_CAF2_H

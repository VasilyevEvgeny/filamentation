//
// Created by vasilyev on 23.07.2019.
//

#ifndef FILAMENTATION_DISPERSIONEXECUTORFULL_H
#define FILAMENTATION_DISPERSIONEXECUTORFULL_H

#include "base_dispersion.h"

class DispersionFull : public BaseDispersion {
public:
    DispersionFull();
    explicit DispersionFull(std::shared_ptr<BasePulsedBeam>& _pulsed_beam, bool _T);

    ~DispersionFull();

    void process(double dz) override;
};


#endif //FILAMENTATION_DISPERSIONEXECUTORFULL_H

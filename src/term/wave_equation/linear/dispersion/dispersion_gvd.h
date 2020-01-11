//
// Created by vasilyev on 24.07.2019.
//

#ifndef FILAMENTATION_DISPERSIONEXECUTORGVD_H
#define FILAMENTATION_DISPERSIONEXECUTORGVD_H


#include "base_dispersion.h"

class DispersionGVD : public BaseDispersion {
public:
    DispersionGVD();
    explicit DispersionGVD(std::shared_ptr<BasePulsedBeam>& _pulsed_beam);

    ~DispersionGVD();

    std::string mode;

    void process(double dz);
    void process_fft(double dz);
    void process_sweep(double dz);

    void set_mode(const std::string& _mode);


};


#endif //FILAMENTATION_DISPERSIONEXECUTORGVD_H

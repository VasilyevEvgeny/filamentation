//
// Created by vasilyev on 11.07.2019.
//

#ifndef FILAMENTATION_FASTFOURIERTRANSFORM_H
#define FILAMENTATION_FASTFOURIERTRANSFORM_H

#include "term/base_term.h"


class FastFourierTransform {
public:
    FastFourierTransform();
    explicit FastFourierTransform(std::shared_ptr<BasePulsedBeam>& _pulsed_beam);

    ~FastFourierTransform();

    std::shared_ptr<BasePulsedBeam> pulsed_beam;

    void forward();
    void backward();

};


#endif //FILAMENTATION_FASTFOURIERTRANSFORM_H

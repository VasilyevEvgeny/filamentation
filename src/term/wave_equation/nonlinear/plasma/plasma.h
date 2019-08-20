//
// Created by vasilyev on 31.07.2019.
//

#ifndef FILAMENTATION_PLASMA_H
#define FILAMENTATION_PLASMA_H


#include "term/wave_equation/nonlinear/base_nonlinear_term.h"

class Plasma : public BaseNonlinearTerm {
public:
    Plasma();
    explicit Plasma(std::shared_ptr<BasePulsedBeam>& _pulsed_beam, bool _T);

    ~Plasma();
};


#endif //FILAMENTATION_PLASMA_H

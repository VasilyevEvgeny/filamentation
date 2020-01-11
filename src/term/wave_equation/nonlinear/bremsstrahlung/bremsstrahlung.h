//
// Created by vasilyev on 01.08.2019.
//

#ifndef FILAMENTATION_BREMSSTRAHLUNG_H
#define FILAMENTATION_BREMSSTRAHLUNG_H

#include "term/wave_equation/nonlinear/base_nonlinear_term.h"

class Bremsstrahlung: public BaseNonlinearTerm {
public:
    Bremsstrahlung();
    explicit Bremsstrahlung(std::shared_ptr<BasePulsedBeam>& _pulsed_beam, bool _T);

    ~Bremsstrahlung();

};


#endif //FILAMENTATION_BREMSSTRAHLUNG_H

//
// Created by vasilyev on 05.08.2019.
//

#ifndef FILAMENTATION_KINETICEQUATION_H
#define FILAMENTATION_KINETICEQUATION_H

#include "term/base_term.h"

class KineticEquation : public BaseTerm {
public:
    KineticEquation();
    explicit KineticEquation(std::shared_ptr<BasePulsedBeam>& _pulsed_beam, double _v_i_const, double _beta);
    ~KineticEquation();

    double v_i_const;
    double beta;

    double calculate_plasma_increase_full(double I_current, double Ne_current, double R);
    double calculate_plasma_increase_field(double Ne_current, double R);
};


#endif //FILAMENTATION_KINETICEQUATION_H

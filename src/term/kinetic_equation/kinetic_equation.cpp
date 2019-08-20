//
// Created by vasilyev on 05.08.2019.
//

#include "kinetic_equation.h"

#define base BaseTerm


KineticEquation::KineticEquation() = default;


KineticEquation::KineticEquation(std::shared_ptr<BasePulsedBeam>& _pulsed_beam, double _v_i_const, double _beta)
: BaseTerm(_pulsed_beam, false)
, v_i_const(_v_i_const)
, beta(_beta){

    base::name = "kinetic_equation";

    base::formula = R"( \frac{\partial N_e(r,t)}{\partial t} =& \ R_E \Bigl[ N_0 - N_e(r,t) \Bigr] + \nu_i N_e(r,t) - \beta N_e(r,t) )";

}


KineticEquation::~KineticEquation() = default;


double KineticEquation::calculate_plasma_increase_full(double I_current, double Ne_current, double R) {
    double N0 = base::pulsed_beam->medium->N_0;
    double dt = base::pulsed_beam->dt;

    double summ = v_i_const * I_current - R - beta;

    if (summ != 0.0) {
        return (Ne_current + R * N0 / summ) * (exp(summ * dt) - 1.0);
    }
    else {
        return 0.0;
    }
}


double KineticEquation::calculate_plasma_increase_field(double Ne, double R) {
    double N0 = base::pulsed_beam->medium->N_0;
    double dt = base::pulsed_beam->dt;

    return (N0 - Ne) * (1.0 - exp(-R * dt));
}


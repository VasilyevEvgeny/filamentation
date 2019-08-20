//
// Created by vasilyev on 05.08.2019.
//

#include "dissipation.h"


#define base BaseTerm
#define base_nonlinear BaseNonlinearTerm

#define ii constants.M_COMPLEX_I
#define m_e constants.m_e
#define eps_0 constants.epsilon_0
#define e constants.e
#define c constants.c

#define omega_0 BaseTerm::pulsed_beam->omega_0
#define i_0 BaseTerm::pulsed_beam->i_0
#define dt BaseTerm::pulsed_beam->dt

#define k_0 BaseTerm::pulsed_beam->medium->k_0
#define n_0 BaseTerm::pulsed_beam->medium->n_0
#define n_2 BaseTerm::pulsed_beam->medium->n_2
#define v_ei BaseTerm::pulsed_beam->medium->v_ei
#define K BaseTerm::pulsed_beam->medium->K


Dissipation::Dissipation() = default;


Dissipation::Dissipation(std::shared_ptr<BasePulsedBeam>& _pulsed_beam)
: BaseNonlinearTerm(_pulsed_beam, false) {

    delta = base::pulsed_beam->medium->delta;

    base::name = "dissipation";

    base::formula = R"( - i k_0 (\alpha + \delta) A(r, t, z) )";

}


Dissipation::~Dissipation() = default;


void Dissipation::update_R_dissipation(double I, double Ne_increase_field) {
    double alpha = 0.0;
    if (I > base::pulsed_beam->medium->ionization->i_start) {
        alpha = Ne_increase_field * K * constants.h_bar * omega_0 / (I * dt);
    }

    base_nonlinear::R_dissipation = -0.5 * (alpha + delta);
}

//
// Created by vasilyev on 31.07.2019.
//

#include "plasma.h"

#define base BaseTerm
#define base_nonlinear BaseNonlinearTerm

#define ii constants.M_COMPLEX_I
#define m_e constants.m_e
#define eps_0 constants.epsilon_0
#define e constants.e
#define c constants.c

#define omega_0 BaseTerm::pulsed_beam->omega_0
#define i_0 BaseTerm::pulsed_beam->i_0

#define k_0 BaseTerm::pulsed_beam->medium->k_0
#define n_0 BaseTerm::pulsed_beam->medium->n_0
#define n_2 BaseTerm::pulsed_beam->medium->n_2



Plasma::Plasma() = default;


Plasma::Plasma(std::shared_ptr<BasePulsedBeam>& _pulsed_beam,
               bool _T)
: BaseNonlinearTerm(_pulsed_beam, _T) {

    base::name = "plasma";

    base_nonlinear::R_plasma = ii * pow(e, 2) * k_0 / (2.0 * m_e * pow(omega_0 * n_0, 2) * eps_0);

    if (base::T) {
        base_nonlinear::R_plasma_T = -pow(e, 2) * k_0 / (2.0 * m_e * pow(omega_0, 3) * pow(n_0, 2) * eps_0);
    }


    if (!base:: T) {
        base::formula = R"( + \frac{2 k_0^2}{n_0} \Delta n_{pl} A(r, t, z) )";
    }
    else {
        base::formula = R"( + \hat{T}^{-1} \frac{2 k_0^2}{n_0} \Delta n_{pl} A(r, t, z) )";
    }
}


Plasma::~Plasma() = default;

//
// Created by vasilyev on 01.08.2019.
//

#include "bremsstrahlung.h"

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
#define v_ei BaseTerm::pulsed_beam->medium->v_ei


Bremsstrahlung::Bremsstrahlung() = default;

Bremsstrahlung::Bremsstrahlung(std::shared_ptr<BasePulsedBeam>& _pulsed_beam,
                               bool _T)
: BaseNonlinearTerm(_pulsed_beam,
                    _T) {

    base::name = "bremsstrahlung";

    base_nonlinear::R_bremsstrahlung = -pow(e, 2) * v_ei / (2.0 * k_0 * pow(c, 2) * m_e * eps_0 * omega_0);

    if (base::T) {
        base_nonlinear::R_bremsstrahlung_T = -ii * pow(e, 2) * v_ei / (k_0 * pow(c, 2) * m_e * eps_0 * pow(omega_0, 2));
    }


    if (!base::T) {
        base::formula = R"( - i \sigma A(r, t, z) )";
    }
    else {
        base::formula = R"( - i \hat{T}^{-2} \sigma A(r, t, z) )";
    }

}

Bremsstrahlung::~Bremsstrahlung() = default;


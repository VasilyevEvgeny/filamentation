//
// Created by vasilyev on 26.07.2019.
//

#include "kerr.h"

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


Kerr::Kerr() = default;


Kerr::Kerr(std::shared_ptr<BasePulsedBeam>& _pulsed_beam, std::map<std::string, bool>& _kerr_info, bool _T)
: BaseNonlinearTerm(_pulsed_beam, _T)
, kerr_info(_kerr_info) {

    base::name = "kerr";

    if (kerr_info.at("instant") && kerr_info.at("inertial")) {
        g = base::pulsed_beam->medium->g;
    }
    else if (kerr_info["instant"] && !kerr_info["inertial"]) {
        g = 0.0;
    }
    else {
        g = 1.0;
    }

    if (g == 0) {
        base::formula = R"( + \frac{2 k_0^2}{n_0} n_2 I(r,t,z) A(r,t,z) )";
        if (base::T) {
            base::formula = R"( + \hat{T} \frac{2 k_0^2}{n_0} n_2 I(r,t,z) A(r,t,z) )";
        }
    }
    else if (g == 1) {
        base::formula = R"( + \frac{2 k_0^2}{n_0} n_2 \int\limits_{0}^{+\infty} H(\tau) I(r, t - \tau) d\tau )";
        if (base::T) {
            base::formula = R"( + \hat{T} \frac{2 k_0^2}{n_0} n_2 \int\limits_{0}^{+\infty} H(\tau) I(r, t - \tau) d\tau )";
        }
    }
    else {
        base::formula = R"( + \frac{2 k_0^2}{n_0} (1 - g) n_2 I(r,t,z) A(r,t,z) + g n_2 \int\limits_{0}^{+\infty} H(\tau) I(r, t - \tau) d\tau )";
        if (base::T) {
            base::formula = R"( + \hat{T} \biggl[ \frac{2 k_0^2}{n_0} (1 - g) n_2 I(r,t,z) A(r,t,z) + g n_2 \int\limits_{0}^{+\infty} H(\tau) I(r, t - \tau) d\tau \biggr] )";
        }
    }

    base_nonlinear::R_kerr_instant = -ii * k_0 * (1.0 - g) * n_2 / n_0;
    if (base::T) {
        base_nonlinear::R_kerr_instant_T = -k_0 * (1.0 - g) * n_2 / (n_0 * omega_0);
    }

}

Kerr::~Kerr() = default;

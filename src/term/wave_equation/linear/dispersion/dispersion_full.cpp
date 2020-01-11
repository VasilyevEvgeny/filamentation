//
// Created by vasilyev on 23.07.2019.
//

#include "dispersion_full.h"

#define base BaseLinearTerm
#define pb BaseTerm::pulsed_beam


DispersionFull::DispersionFull() = default;


DispersionFull::DispersionFull(std::shared_ptr<BasePulsedBeam>& _pulsed_beam,
                               bool _T)
: BaseDispersion(_pulsed_beam, _T) {

    base::name = "dispersion_full";

    if (base::T) {
        base::formula = R"( + \hat{T}^{-1} \frac1{2 \pi} \int\limits_{-\infty}^{+\infty}
        \Bigl( k^2(\omega_0 + \Omega) - (k_0 + k_1 \Omega)^2 \Bigr) \tilde{A}(r, \Omega, z)
        \exp \{ i \Omega t \} d \Omega )";
    } else {
        base::formula = R"( +\frac1{2 \pi} \int\limits_{-\infty}^{+\infty}
        \Bigl( k^2(\omega_0 + \Omega) - (k_0 + k_1 \Omega)^2 \Bigr) \tilde{A}(r, \Omega, z)
        \exp \{ i \Omega t \} d \Omega )";
    }

    }

DispersionFull::~DispersionFull() = default;


void DispersionFull::process(double dz) {

#pragma omp parallel
    {
#pragma omp for
        for (size_t k = 0; k < pb->n_r; ++k) {
            for (size_t s = 0; s < pb->n_t; ++s) {
                std::complex<double> R_disp_full = (pow(pb->medium->calculate_k(pb->Omegas[s] + pb->omega_0), 2) -
                        pow(pb->medium->k_0 + pb->medium->k_1 * pb->Omegas[s], 2)) / (2j * pb->medium->k_0);

                pb->spectrum[k][s] *= exp(R_disp_full * dz);
            }
        }
    }
}


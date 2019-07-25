//
// Created by vasilyev on 16.07.2019.
//

#include <vector>
#include <complex>


#include "diffraction_executor.h"


#define base BaseTerm<PulsedBeam<Medium>>
#define pb BaseTerm<PulsedBeam<Medium>>::pulsed_beam

template<template<typename, typename...> class PulsedBeam, typename Medium>
DiffractionExecutor<PulsedBeam<Medium>>::DiffractionExecutor() = default;


template<template<typename, typename...> class PulsedBeam, typename Medium>
DiffractionExecutor<PulsedBeam<Medium>>::DiffractionExecutor(PulsedBeam<Medium>* _pulsed_beam) :
        BaseTerm<PulsedBeam <Medium>>(_pulsed_beam) {

    base::name = "diffraction";
    base::formula = R"( +\biggl( \frac{\partial^2}{\partial r^2} +
\frac1{r} \frac{\partial}{\partial r} -
\frac{m^2}{r^2} \biggr) A(r,t,z) )";

}


template<template<typename, typename...> class PulsedBeam, typename Medium>
void DiffractionExecutor<PulsedBeam<Medium>>::process(double dz) {

#pragma omp parallel
    {
        double c1 = 1.0 / (2.0 * pow(pb->dr, 2));
        double c2 = 1.0 / (4.0 * pb->dr);
        std::complex<double> c3 = 2j * pb->medium->k_0;

        std::vector<double> alpha(pb->n_r, 0.0);
        std::vector<std::complex<double>> beta(pb->n_r, 0.0);
        std::vector<double> gamma(pb->n_r, 0.0);
        std::vector<double> vx(pb->n_r, 0.0);

        for (size_t k = 1; k < pb->n_r - 1; ++k) {
            alpha[k] = c1 + c2 / pb->rs[k];
            gamma[k] = c1 - c2 / pb->rs[k];
            vx[k] = pow(pb->m / pb->rs[k], 2);
        }

        std::vector<std::complex<double>> delta(pb->n_r, 0.0);
        std::vector<std::complex<double>> xi(pb->n_r, 0.0);
        std::vector<std::complex<double>> eta(pb->n_r, 0.0);

        double kappa_left = 1.0;
        double mu_left = 0.0;
        double kappa_right = 0.0;
        double mu_right = 0.0;

#pragma omp for
        for (size_t s = 0; s < pb->n_t; ++s) {
            /* straight course */

            xi[1] = kappa_left;
            eta[1] = mu_left;

            for (size_t k = 1; k < pb->n_r - 1; ++k) {
                beta[k] = 2.0 * c1 + c3 / dz + vx[k];

                delta[k] = alpha[k] * pb->spectrum[k + 1][s] -
                        (std::conj(beta[k]) - vx[k]) * pb->spectrum[k][s] +
                        gamma[k] * pb->spectrum[k - 1][s];

                xi[k + 1] = alpha[k] / (beta[k] - gamma[k] * xi[k]);
                eta[k + 1] = (delta[k] + gamma[k] * eta[k]) / (beta[k] - gamma[k] * xi[k]);
            }

            /* reversal course */
            pb->spectrum[pb->n_r - 1][s] = (mu_right + kappa_right * eta[pb->n_r - 1]) /
                    (1.0 - kappa_right * xi[pb->n_r - 1]);

            for (size_t k = pb->n_r - 1; k > 0; --k)
                pb->spectrum[k - 1][s] = xi[k] * pb->spectrum[k][s] + eta[k];
        }

        alpha.erase(alpha.begin(), alpha.end());
        beta.erase(beta.begin(), beta.end());
        gamma.erase(gamma.begin(), gamma.end());
        delta.erase(delta.begin(), delta.end());
        xi.erase(xi.begin(), xi.end());
        eta.erase(eta.begin(), eta.end());
    }
}


template<template<typename, typename...> class PulsedBeam, typename Medium>
DiffractionExecutor<PulsedBeam<Medium>>::~DiffractionExecutor() = default;



template class DiffractionExecutor<Gauss<SiO2>>;
template class DiffractionExecutor<Ring<SiO2>>;
template class DiffractionExecutor<Vortex<SiO2>>;
template class DiffractionExecutor<Gauss<CaF2>>;
template class DiffractionExecutor<Ring<CaF2>>;
template class DiffractionExecutor<Vortex<CaF2>>;
template class DiffractionExecutor<Gauss<LiF>>;
template class DiffractionExecutor<Ring<LiF>>;
template class DiffractionExecutor<Vortex<LiF>>;

//
// Created by vasilyev on 24.07.2019.
//

#include "dispersion_gvd.h"

#define base BaseLinearTerm<PulsedBeam<Medium>>
#define pb BaseTerm<PulsedBeam<Medium>>::pulsed_beam


template<template<typename, typename...> class PulsedBeam, typename Medium>
DispersionGVD<PulsedBeam<Medium>>::DispersionGVD() = default;


template<template<typename, typename...> class PulsedBeam, typename Medium>
DispersionGVD<PulsedBeam<Medium>>::DispersionGVD(PulsedBeam<Medium>* _pulsed_beam, std::string& _mode)
: BaseDispersion<PulsedBeam <Medium>>(_pulsed_beam)
, mode(_mode){

        base::name = "dispersion_gvd";
        base::formula = R"( -k_0 k_2 \frac{\partial^2 A(r,t,z)}{\partial t^2} )";
}

template<template<typename, typename...> class PulsedBeam, typename Medium>
DispersionGVD<PulsedBeam<Medium>>::~DispersionGVD() = default;



template<template<typename, typename...> class PulsedBeam, typename Medium>
void DispersionGVD<PulsedBeam<Medium>>::process(double dz) {
    if (mode == "fft") {
        return process_fft(dz);
    }
    else if (mode == "sweep") {
        return process_sweep(dz);
    }

}

template<template<typename, typename...> class PulsedBeam, typename Medium>
void DispersionGVD<PulsedBeam<Medium>>::process_fft(double dz) {

#pragma omp parallel
    {
#pragma omp for
        for (size_t k = 0; k < pb->n_r; ++k) {
            for (size_t s = 0; s < pb->n_t; ++s) {
                std::complex<double> R_disp_gvd = -0.5j * pb->medium->k_2 * pow(pb->Omegas[s], 2);

                pb->spectrum[k][s] *= exp(R_disp_gvd * dz);
            }
        }
    }

}


template<template<typename, typename...> class PulsedBeam, typename Medium>
void DispersionGVD<PulsedBeam<Medium>>::process_sweep(double dz) {

#pragma omp parallel
    {
        std::complex<double> R = 0.5j * pb->medium->k_2;
        std::complex<double> alpha = 0.5 * R / pow(pb->dt, 2);
        std::complex<double> gamma = 0.5 * R / pow(pb->dt, 2);
        std::complex<double> beta = 1.0 / dz + R / pow(pb->dt, 2);

        std::vector<std::complex<double>> delta(pb->n_t, 0.0);
        std::vector<std::complex<double>> xi(pb->n_t, 0.0);
        std::vector<std::complex<double>> eta(pb->n_t, 0.0);

        double kappa_left = 0.0;
        double mu_left = 0.0;
        double kappa_right = 0.0;
        double mu_right = 0.0;

#pragma omp for
        for (size_t k = 0; k < pb->n_r; ++k) {

            /* straight course */
            xi[1] = kappa_left;
            eta[1] = mu_left;

            for (size_t s = 1; s < pb->n_t - 1; ++s) {

                delta[s] = alpha * pb->field[k][s + 1] +
                           conj(beta) * pb->field[k][s] +
                           gamma * pb->field[k][s - 1];

                xi[s + 1] = alpha / (beta - gamma * xi[s]);
                eta[s + 1] = (delta[s] + gamma * eta[s]) / (beta - gamma * xi[s]);
            }

            /* reversal course */
            pb->field[k][pb->n_t - 1] = (mu_right + kappa_right * eta[pb->n_t - 1]) /
                                           (1.0 - kappa_right * xi[pb->n_t - 1]);

            for (size_t s = pb->n_t - 1; s > 0; --s)
                pb->field[k][s - 1] = xi[s] * pb->field[k][s] + eta[s];
        }

        delta.erase(delta.begin(), delta.end());
        xi.erase(xi.begin(), xi.end());
        eta.erase(eta.begin(), eta.end());
    }
}



template class DispersionGVD<Gauss<SiO2>>;
template class DispersionGVD<Gauss<CaF2>>;
template class DispersionGVD<Gauss<LiF>>;
template class DispersionGVD<Ring<SiO2>>;
template class DispersionGVD<Ring<CaF2>>;
template class DispersionGVD<Ring<LiF>>;
template class DispersionGVD<Vortex<SiO2>>;
template class DispersionGVD<Vortex<CaF2>>;
template class DispersionGVD<Vortex<LiF>>;

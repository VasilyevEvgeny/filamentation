//
// Created by vasilyev on 23.07.2019.
//

#include "dispersion_executor_full.h"

#define pb BaseTerm<PulsedBeam<Medium>>::pulsed_beam


template<template<typename, typename...> class PulsedBeam, typename Medium>
DispersionExecutorFull<PulsedBeam<Medium>>::DispersionExecutorFull() = default;


template<template<typename, typename...> class PulsedBeam, typename Medium>
DispersionExecutorFull<PulsedBeam<Medium>>::DispersionExecutorFull(PulsedBeam<Medium>* _pulsed_beam) :
        BaseDispersionExecutor<PulsedBeam <Medium>>(_pulsed_beam) {


}

template<template<typename, typename...> class PulsedBeam, typename Medium>
DispersionExecutorFull<PulsedBeam<Medium>>::~DispersionExecutorFull() = default;



template<template<typename, typename...> class PulsedBeam, typename Medium>
void DispersionExecutorFull<PulsedBeam<Medium>>::process(double dz) {

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


template class DispersionExecutorFull<Gauss<SiO2>>;
template class DispersionExecutorFull<Gauss<CaF2>>;
template class DispersionExecutorFull<Gauss<LiF>>;
template class DispersionExecutorFull<Ring<SiO2>>;
template class DispersionExecutorFull<Ring<CaF2>>;
template class DispersionExecutorFull<Ring<LiF>>;
template class DispersionExecutorFull<Vortex<SiO2>>;
template class DispersionExecutorFull<Vortex<CaF2>>;
template class DispersionExecutorFull<Vortex<LiF>>;

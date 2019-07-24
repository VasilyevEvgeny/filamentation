//
// Created by vasilyev on 24.07.2019.
//

#include "dispersion_executor_gvd.h"

#define pb BaseTerm<PulsedBeam<Medium>>::pulsed_beam


template<template<typename, typename...> class PulsedBeam, typename Medium>
DispersionExecutorGVD<PulsedBeam<Medium>>::DispersionExecutorGVD() = default;


template<template<typename, typename...> class PulsedBeam, typename Medium>
DispersionExecutorGVD<PulsedBeam<Medium>>::DispersionExecutorGVD(PulsedBeam<Medium>* _pulsed_beam, std::string& _mode)
: BaseDispersionExecutor<PulsedBeam <Medium>>(_pulsed_beam)
, mode(_mode){



}

template<template<typename, typename...> class PulsedBeam, typename Medium>
DispersionExecutorGVD<PulsedBeam<Medium>>::~DispersionExecutorGVD() = default;



template<template<typename, typename...> class PulsedBeam, typename Medium>
void DispersionExecutorGVD<PulsedBeam<Medium>>::process(double dz) {
    if (mode == "fft") {
        return process_fft(dz);
    }
    else if (mode == "sweep") {
        return process_sweep(dz);
    }

}

template<template<typename, typename...> class PulsedBeam, typename Medium>
void DispersionExecutorGVD<PulsedBeam<Medium>>::process_fft(double dz) {

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
void DispersionExecutorGVD<PulsedBeam<Medium>>::process_sweep(double dz) {

}



template class DispersionExecutorGVD<Gauss<SiO2>>;
template class DispersionExecutorGVD<Gauss<CaF2>>;
template class DispersionExecutorGVD<Gauss<LiF>>;
template class DispersionExecutorGVD<Ring<SiO2>>;
template class DispersionExecutorGVD<Ring<CaF2>>;
template class DispersionExecutorGVD<Ring<LiF>>;
template class DispersionExecutorGVD<Vortex<SiO2>>;
template class DispersionExecutorGVD<Vortex<CaF2>>;
template class DispersionExecutorGVD<Vortex<LiF>>;

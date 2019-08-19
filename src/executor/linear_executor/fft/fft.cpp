//
// Created by vasilyev on 11.07.2019.
//

#include "fasttransforms.h"

#include "fft.h"

template<template<typename, typename...> class PulsedBeam, typename Medium>
FastFourierTransform<PulsedBeam<Medium>>::FastFourierTransform() = default;


template<template<typename, typename...> class PulsedBeam, typename Medium>
FastFourierTransform<PulsedBeam<Medium>>::FastFourierTransform(std::shared_ptr<PulsedBeam<Medium>> _pulsed_beam)
: pulsed_beam(_pulsed_beam) {


}


template<template<typename, typename...> class PulsedBeam, typename Medium>
FastFourierTransform<PulsedBeam<Medium>>::~FastFourierTransform() = default;



template<template<typename, typename...> class PulsedBeam, typename Medium>
void FastFourierTransform<PulsedBeam<Medium>>::forward() {

    alglib::complex_1d_array slice;

#pragma omp parallel private(slice)
    {
        slice.setcontent(pulsed_beam->n_t, &std::vector<alglib::complex>(pulsed_beam->n_t, 0.0)[0]);

#pragma omp for
        for (size_t k = 0; k < pulsed_beam->n_r; ++k) {
            for (size_t s = 0; s < pulsed_beam->n_t; ++s) {
                slice[s] = alglib::complex(pulsed_beam->field[k][s].real(), pulsed_beam->field[k][s].imag());
            }

            alglib::fftc1d(slice);

            for (size_t s = 0; s < pulsed_beam->n_t; ++s) {
                pulsed_beam->spectrum[k][s] = std::complex<double>(slice[s].x, slice[s].y);
            }
        }
    }
}

template<template<typename, typename...> class PulsedBeam, typename Medium>
void FastFourierTransform<PulsedBeam<Medium>>::backward() {
    alglib::complex_1d_array slice;

#pragma omp parallel private(slice)
    {
        slice.setcontent(pulsed_beam->n_t, &std::vector<alglib::complex>(pulsed_beam->n_t, 0.0)[0]);

#pragma omp for
        for (size_t k = 0; k < pulsed_beam->n_r; ++k) {
            for (size_t s = 0; s < pulsed_beam->n_t; ++s) {
                slice[s] = alglib::complex(pulsed_beam->spectrum[k][s].real(), pulsed_beam->spectrum[k][s].imag());
            }

            alglib::fftc1dinv(slice);

            for (size_t s = 0; s < pulsed_beam->n_t; ++s) {
                pulsed_beam->field[k][s] = std::complex<double>(slice[s].x, slice[s].y);
            }
        }
    }
}


template class FastFourierTransform<Gauss<SiO2>>;
template class FastFourierTransform<Gauss<CaF2>>;
template class FastFourierTransform<Gauss<LiF>>;
template class FastFourierTransform<Ring<SiO2>>;
template class FastFourierTransform<Ring<CaF2>>;
template class FastFourierTransform<Ring<LiF>>;
template class FastFourierTransform<Vortex<SiO2>>;
template class FastFourierTransform<Vortex<CaF2>>;
template class FastFourierTransform<Vortex<LiF>>;

template class FastFourierTransform<BasePulsedBeam<BaseMedium>>;


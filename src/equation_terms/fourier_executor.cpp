//
// Created by vasilyev on 11.07.2019.
//

#include "../../lib/alglib/src/fasttransforms.h"

#include "fourier_executor.h"

template<template<typename, typename...> class PulsedBeam, typename Medium>
FourierExecutor<PulsedBeam<Medium>>::FourierExecutor() = default;


template<template<typename, typename...> class PulsedBeam, typename Medium>
FourierExecutor<PulsedBeam<Medium>>::FourierExecutor(PulsedBeam<Medium>* _pulsed_beam) :
        BaseTerm<PulsedBeam <Medium>>(_pulsed_beam) {



}


template<template<typename, typename...> class PulsedBeam, typename Medium>
void FourierExecutor<PulsedBeam<Medium>>::forward() {

    alglib::complex_1d_array slice;

#pragma omp parallel private(slice)
    {
        slice.setcontent(BaseTerm<PulsedBeam<Medium>>::pulsed_beam->n_t,
                         &std::vector<alglib::complex>(BaseTerm<PulsedBeam<Medium>>::pulsed_beam->n_t, 0.0)[0]);

#pragma omp for
        for (size_t k = 0; k < BaseTerm<PulsedBeam<Medium>>::pulsed_beam->n_r; ++k) {
            for (size_t s = 0; s < BaseTerm<PulsedBeam<Medium>>::pulsed_beam->n_t; ++s) {
                slice[s] = alglib::complex(BaseTerm<PulsedBeam<Medium>>::pulsed_beam->field[k][s].real(),
                                           BaseTerm<PulsedBeam<Medium>>::pulsed_beam->field[k][s].imag());
            }

            alglib::fftc1d(slice);

            for (size_t s = 0; s < BaseTerm<PulsedBeam<Medium>>::pulsed_beam->n_t; ++s) {
                BaseTerm<PulsedBeam<Medium>>::pulsed_beam->spectrum[k][s] = std::complex<double>(slice[s].x,
                                                                                                 slice[s].y);
            }
        }
    }

}

template<template<typename, typename...> class PulsedBeam, typename Medium>
void FourierExecutor<PulsedBeam<Medium>>::backward() {
    alglib::complex_1d_array slice;

#pragma omp parallel private(slice)
{
    slice.setcontent(BaseTerm<PulsedBeam<Medium>>::pulsed_beam->n_t,
                     &std::vector<alglib::complex>(BaseTerm<PulsedBeam<Medium>>::pulsed_beam->n_t, 0.0)[0]);

#pragma omp for
    for (size_t k = 0; k < BaseTerm<PulsedBeam<Medium>>::pulsed_beam->n_r; ++k) {
        for (size_t s = 0; s < BaseTerm<PulsedBeam<Medium>>::pulsed_beam->n_t; ++s) {
            slice[s] = alglib::complex(BaseTerm<PulsedBeam<Medium>>::pulsed_beam->spectrum[k][s].real(),
                                       BaseTerm<PulsedBeam<Medium>>::pulsed_beam->spectrum[k][s].imag());
        }

        alglib::fftc1dinv(slice);

        for (size_t s = 0; s < BaseTerm<PulsedBeam<Medium>>::pulsed_beam->n_t; ++s) {
            BaseTerm<PulsedBeam<Medium>>::pulsed_beam->field[k][s] =
                    std::complex<double>(slice[s].x, slice[s].y);
        }
    }
}

}


template
class FourierExecutor<Gauss<SiO2>>;

template
class FourierExecutor<Gauss<CaF2>>;

template
class FourierExecutor<Gauss<LiF>>;

template
class FourierExecutor<Ring<SiO2>>;

template
class FourierExecutor<Ring<CaF2>>;

template
class FourierExecutor<Ring<LiF>>;

template
class FourierExecutor<Vortex<SiO2>>;

template
class FourierExecutor<Vortex<CaF2>>;

template
class FourierExecutor<Vortex<LiF>>;
//
// Created by vasilyev on 11.07.2019.
//

#include "fasttransforms.h"
#include "fft.h"


FastFourierTransform::FastFourierTransform() = default;


FastFourierTransform::FastFourierTransform(std::shared_ptr<BasePulsedBeam>& _pulsed_beam)
: pulsed_beam(_pulsed_beam) {

}


FastFourierTransform::~FastFourierTransform() = default;


void FastFourierTransform::forward() {

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


void FastFourierTransform::backward() {
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


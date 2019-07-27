//
// Created by vasilyev on 27.07.2019.
//

#include "nonlinear_executor.h"

#define base BaseExecutor<PulsedBeam<Medium>>

template<template<typename, typename...> class PulsedBeam, typename Medium>
NonlinearExecutor<PulsedBeam<Medium>>::NonlinearExecutor() = default;


template<template<typename, typename...> class PulsedBeam, typename Medium>
NonlinearExecutor<PulsedBeam<Medium>>::NonlinearExecutor(PulsedBeam<Medium>* _pulsed_beam,
                                                         std::vector<std::string>& _active_nonlinear_terms,
                                                         std::map<std::string, BaseNonlinearTerm<PulsedBeam<Medium>>*>& _nonlinear_terms_pool)
: BaseExecutor<PulsedBeam<Medium>>(_pulsed_beam, _active_nonlinear_terms)
, nonlinear_terms_pool(_nonlinear_terms_pool) {



}


template<template<typename, typename...> class PulsedBeam, typename Medium>
NonlinearExecutor<PulsedBeam<Medium>>::~NonlinearExecutor() = default;



template<template<typename, typename...> class PulsedBeam, typename Medium>
void NonlinearExecutor<PulsedBeam<Medium>>::execute(double dz) {

    for(size_t k = 0; k < base::pulsed_beam->n_r; ++k) {
        for(size_t s = 0; s < base::pulsed_beam->n_t; ++s) {

            std::complex<double> increment = std::complex<double>(0.0, 0.0);
            for(auto& nonlinear_term_name : base::active_terms) {

                increment += nonlinear_terms_pool[nonlinear_term_name]->R;
            }



            base::pulsed_beam->field[k][s] *= exp(increment * norm(base::pulsed_beam->field[k][s]) * dz);

        }
    }

}

template class NonlinearExecutor<Gauss<SiO2>>;
template class NonlinearExecutor<Gauss<CaF2>>;
template class NonlinearExecutor<Gauss<LiF>>;
template class NonlinearExecutor<Ring<SiO2>>;
template class NonlinearExecutor<Ring<CaF2>>;
template class NonlinearExecutor<Ring<LiF>>;
template class NonlinearExecutor<Vortex<SiO2>>;
template class NonlinearExecutor<Vortex<CaF2>>;
template class NonlinearExecutor<Vortex<LiF>>;
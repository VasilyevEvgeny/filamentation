//
// Created by vasilyev on 27.07.2019.
//

#include "linear_executor.h"


#define base BaseExecutor<PulsedBeam<Medium>>

template<template<typename, typename...> class PulsedBeam, typename Medium>
LinearExecutor<PulsedBeam<Medium>>::LinearExecutor() = default;


template<template<typename, typename...> class PulsedBeam, typename Medium>
LinearExecutor<PulsedBeam<Medium>>::LinearExecutor(PulsedBeam<Medium>* _pulsed_beam,
                                                   std::vector<std::string>& _active_linear_terms,
                                                   std::map<std::string, BaseLinearTerm<PulsedBeam<Medium>>*>& _linear_terms_pool)
: BaseExecutor<PulsedBeam<Medium>>(_pulsed_beam, _active_linear_terms)
, linear_terms_pool(_linear_terms_pool) {

    fft = FastFourierTransform<PulsedBeam<Medium>>(base::pulsed_beam);

}


template<template<typename, typename...> class PulsedBeam, typename Medium>
LinearExecutor<PulsedBeam<Medium>>::~LinearExecutor() = default;


template<template<typename, typename...> class PulsedBeam, typename Medium>
void LinearExecutor<PulsedBeam<Medium>>::execute(double dz) {

    fft.forward();

    for(auto& linear_term_name : base::active_terms) {
        linear_terms_pool[linear_term_name]->process(dz);
    }

    fft.backward();

}


template class LinearExecutor<Gauss<SiO2>>;
template class LinearExecutor<Gauss<CaF2>>;
template class LinearExecutor<Gauss<LiF>>;
template class LinearExecutor<Ring<SiO2>>;
template class LinearExecutor<Ring<CaF2>>;
template class LinearExecutor<Ring<LiF>>;
template class LinearExecutor<Vortex<SiO2>>;
template class LinearExecutor<Vortex<CaF2>>;
template class LinearExecutor<Vortex<LiF>>;
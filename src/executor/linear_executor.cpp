//
// Created by vasilyev on 27.07.2019.
//

#include "linear_executor.h"


#define base BaseExecutor<PulsedBeam<Medium>>

template<template<typename, typename...> class PulsedBeam, typename Medium>
LinearExecutor<PulsedBeam<Medium>>::LinearExecutor() = default;


template<template<typename, typename...> class PulsedBeam, typename Medium>
LinearExecutor<PulsedBeam<Medium>>::LinearExecutor(ConfigManager& _config_manager,
                                                   std::shared_ptr<PulsedBeam<Medium>> _pulsed_beam)
: BaseExecutor<PulsedBeam<Medium>>(_pulsed_beam)
, config_manager(_config_manager) {

    fft = FastFourierTransform<PulsedBeam<Medium>>(base::pulsed_beam);

    diffraction = std::make_shared<Diffraction<PulsedBeam<Medium>>>(base::pulsed_beam, config_manager.T.at("diffraction"));
    dispersion_full = std::make_shared<DispersionFull<PulsedBeam<Medium>>>(base::pulsed_beam, config_manager.T.at("dispersion"));
    dispersion_gvd = std::make_shared<DispersionGVD<PulsedBeam<Medium>>>(base::pulsed_beam);

    // container for linear terms
    terms_pool.insert(std::pair<std::string, std::shared_ptr<BaseLinearTerm<PulsedBeam<Medium>>>>(diffraction->name, diffraction));
    terms_pool.insert(std::pair<std::string, std::shared_ptr<BaseLinearTerm<PulsedBeam<Medium>>>>(dispersion_full->name, dispersion_full));
    terms_pool.insert(std::pair<std::string, std::shared_ptr<BaseLinearTerm<PulsedBeam<Medium>>>>(dispersion_gvd->name, dispersion_gvd));

}


template<template<typename, typename...> class PulsedBeam, typename Medium>
LinearExecutor<PulsedBeam<Medium>>::~LinearExecutor() = default;


template<template<typename, typename...> class PulsedBeam, typename Medium>
void LinearExecutor<PulsedBeam<Medium>>::execute(double dz) {

    fft.forward();

    for(auto& linear_term_name : config_manager.active_linear_terms) {
        terms_pool[linear_term_name]->process(dz);
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

template class LinearExecutor<BasePulsedBeam<BaseMedium>>;
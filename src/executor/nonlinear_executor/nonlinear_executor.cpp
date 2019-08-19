//
// Created by vasilyev on 27.07.2019.
//

#include "nonlinear_executor.h"

#define base BaseExecutor<PulsedBeam<Medium>>
#define pb BaseExecutor<PulsedBeam<Medium>>::pulsed_beam
#define dt BaseExecutor<PulsedBeam<Medium>>::pulsed_beam->dt

template<template<typename, typename...> class PulsedBeam, typename Medium>
NonlinearExecutor<PulsedBeam<Medium>>::NonlinearExecutor() = default;


template<template<typename, typename...> class PulsedBeam, typename Medium>
NonlinearExecutor<PulsedBeam<Medium>>::NonlinearExecutor(
        ConfigManager& _config_manager,
        std::shared_ptr<PulsedBeam<Medium>> _pulsed_beam)
: BaseExecutor<PulsedBeam<Medium>>(_pulsed_beam)
, config_manager(_config_manager) {

    // nonlinear terms
    kerr = std::make_shared<Kerr<PulsedBeam<Medium>>>(base::pulsed_beam, config_manager.kerr_info, config_manager.T.at("kerr"));
    plasma = std::make_shared<Plasma<PulsedBeam<Medium>>>(base::pulsed_beam, config_manager.T.at("plasma"));
    bremsstrahlung = std::make_shared<Bremsstrahlung<PulsedBeam<Medium>>>(base::pulsed_beam, config_manager.T.at("bremsstrahlung"));
    dissipation = std::make_shared<Dissipation<PulsedBeam<Medium>>>(base::pulsed_beam);

    kinetic_equation = std::make_shared<KineticEquation<PulsedBeam<Medium>>>(
            base::pulsed_beam,
            base::pulsed_beam->medium->v_i_const,
            base::pulsed_beam->medium->beta);

    // container for nonlinear terms
    terms_pool.insert(std::pair<std::string, std::shared_ptr<BaseNonlinearTerm<PulsedBeam<Medium>>>>(kerr->name, kerr));
    terms_pool.insert(std::pair<std::string, std::shared_ptr<BaseNonlinearTerm<PulsedBeam<Medium>>>>(plasma->name, plasma));
    terms_pool.insert(std::pair<std::string, std::shared_ptr<BaseNonlinearTerm<PulsedBeam<Medium>>>>(bremsstrahlung->name, bremsstrahlung));
    terms_pool.insert(std::pair<std::string, std::shared_ptr<BaseNonlinearTerm<PulsedBeam<Medium>>>>(dissipation->name, dissipation));


}


template<template<typename, typename...> class PulsedBeam, typename Medium>
NonlinearExecutor<PulsedBeam<Medium>>::~NonlinearExecutor() = default;





template<template<typename, typename...> class PulsedBeam, typename Medium>
void NonlinearExecutor<PulsedBeam<Medium>>::execute(double dz) {

    for(size_t k = 0; k < pb->n_r; ++k) {
        for(size_t s = 1; s < pb->n_t - 1; ++s) {

            // intensity
            double I = norm(pb->field[k][s]) * pb->i_0;
            double I_prev = norm(pb->field[k][s - 1]) * pb->i_0;
            double dI = I - I_prev;

            // ionization rate
            double R = pb->medium->ionization.R(I);

            // plasma
            double Ne = pb->plasma[k][s];
            double Ne_prev = pb->plasma[k][s - 1];
            double dNe = Ne - Ne_prev;

            // dissipation
            double Ne_increase_field = kinetic_equation->calculate_plasma_increase_field(Ne, R);
            dissipation->update_R_dissipation(I, Ne_increase_field);

            std::complex<double> increment = std::complex<double>(0.0, 0.0);
            for(auto& nonlinear_term_name : config_manager.active_nonlinear_terms) {

                increment +=   terms_pool[nonlinear_term_name]->R_kerr_instant * I
                             + terms_pool[nonlinear_term_name]->R_kerr_instant_T * dI / dt
                             + terms_pool[nonlinear_term_name]->R_plasma * Ne
                             + terms_pool[nonlinear_term_name]->R_plasma_T * dNe / dt
                             + terms_pool[nonlinear_term_name]->R_bremsstrahlung * Ne
                             + terms_pool[nonlinear_term_name]->R_bremsstrahlung_T * dNe / dt
                             + terms_pool[nonlinear_term_name]->R_dissipation;
            }

            pb->field[k][s] *= exp(increment * dz);



            // plasma increase
            double Ne_increase_full = kinetic_equation->calculate_plasma_increase_full(I, Ne, R);
            pb->plasma[k][s + 1] = Ne + Ne_increase_full;
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

template class NonlinearExecutor<BasePulsedBeam<BaseMedium>>;
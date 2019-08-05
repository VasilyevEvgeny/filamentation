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
NonlinearExecutor<PulsedBeam<Medium>>::NonlinearExecutor(PulsedBeam<Medium>* _pulsed_beam,
                                                         std::vector<std::string>& _active_nonlinear_terms,
                                                         std::map<std::string, BaseNonlinearTerm<PulsedBeam<Medium>>*>& _nonlinear_terms_pool,
                                                         Dissipation<PulsedBeam<Medium>>* _dissipation)
: BaseExecutor<PulsedBeam<Medium>>(_pulsed_beam, _active_nonlinear_terms)
, nonlinear_terms_pool(_nonlinear_terms_pool)
, dissipation(_dissipation) {

        kinetic_equation = KineticEquation<PulsedBeam<Medium>>(
                base::pulsed_beam,
                base::pulsed_beam->medium->v_i_const,
                base::pulsed_beam->medium->beta);

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
            double Ne_increase_field = kinetic_equation.calculate_plasma_increase_field(Ne, R);
            dissipation->update_R_dissipation(I, Ne_increase_field);

            std::complex<double> increment = std::complex<double>(0.0, 0.0);
            for(auto& nonlinear_term_name : base::active_terms) {

                increment +=   nonlinear_terms_pool[nonlinear_term_name]->R_kerr_instant * I
                             + nonlinear_terms_pool[nonlinear_term_name]->R_kerr_instant_T * dI / dt
                             + nonlinear_terms_pool[nonlinear_term_name]->R_plasma * Ne
                             + nonlinear_terms_pool[nonlinear_term_name]->R_plasma_T * dNe / dt
                             + nonlinear_terms_pool[nonlinear_term_name]->R_bremsstrahlung * Ne
                             + nonlinear_terms_pool[nonlinear_term_name]->R_bremsstrahlung_T * dNe / dt
                             + nonlinear_terms_pool[nonlinear_term_name]->R_dissipation;
            }

            pb->field[k][s] *= exp(increment * dz);



            // plasma increase
            double Ne_increase_full = kinetic_equation.calculate_plasma_increase_full(I, Ne, R);
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
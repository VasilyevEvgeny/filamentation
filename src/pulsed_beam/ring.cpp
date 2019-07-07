//
// Created by vasilyev on 04.07.2019.
//

#include "ring.h"

template<typename Medium>
Ring<Medium>::Ring(Medium medium,
                     double _lambda_0,
                     size_t _M,
                     double _r_0,
                     size_t _n_r,
                     double _t_0,
                     size_t _n_t,
                     double _p0_to_p_cr) : BasePulsedBeam<Medium>(medium,
                                                             _lambda_0,
                                                             _r_0,
                                                             _n_r,
                                                             _t_0,
                                                             _n_t,
                                                             _p0_to_p_cr) {

    Ring<Medium>::info = "ring";

    Ring<Medium>::M = _M;


    Ring<Medium>::p_cr_to_p_g = Ring<Medium>::calculate_p_cr_to_p_g();
    Ring<Medium>::p_0 = BasePulsedBeam<Medium>::calculate_p_0();

    Ring<Medium>::i_0 = BasePulsedBeam<Medium>::calculate_i_0();

    BasePulsedBeam<Medium>::initialize_field();

    Ring<Medium>::e_0 = BasePulsedBeam<Medium>::calculate_e_0();
}

template<typename Medium>
Ring<Medium>::~Ring() = default;


template<typename Medium>
double Ring<Medium>::calculate_p_cr_to_p_g() {
    return 0.120 * Ring<Medium>::M + 1.012;
}


template class Ring<SiO2>;
template class Ring<CaF2>;
template class Ring<LiF>;
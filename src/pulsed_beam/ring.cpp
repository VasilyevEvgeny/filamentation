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
                     double _p_rel) : BasePulsedBeam<Medium>(medium,
                                                             _lambda_0,
                                                             _r_0,
                                                             _n_r,
                                                             _t_0,
                                                             _n_t,
                                                             _p_rel) {

    Ring<Medium>::info = "ring";

    Ring<Medium>::M = _M;

    Ring<Medium>::p_0 = Ring<Medium>::calculate_p_0();

}

template<typename Medium>
Ring<Medium>::~Ring() = default;

template class Ring<SiO2>;
template class Ring<CaF2>;
template class Ring<LiF>;
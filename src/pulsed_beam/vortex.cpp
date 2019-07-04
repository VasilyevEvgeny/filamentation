//
// Created by vasilyev on 04.07.2019.
//

#include "vortex.h"




template<typename Medium>
Vortex<Medium>::Vortex(Medium _medium,
                       double _lambda_0,
                       size_t _M,
                       size_t _m,
                       double _r_0,
                       size_t _n_r,
                       double _t_0,
                       size_t _n_t,
                       double _p_rel) : BasePulsedBeam<Medium>(_medium,
                                                               _lambda_0,
                                                               _r_0,
                                                               _n_r,
                                                               _t_0,
                                                               _n_t,
                                                               _p_rel) {

    Vortex<Medium>::info = "vortex";

    Vortex<Medium>::M = _M;
    Vortex<Medium>::m = _m;

    Vortex<Medium>::p_0 = Vortex<Medium>::calculate_p_0();

}

template<typename Medium>
Vortex<Medium>::~Vortex() = default;

template class Vortex<SiO2>;
template class Vortex<CaF2>;
template class Vortex<LiF>;


template<typename Medium>
double Vortex<Medium>::calculate_p_0() {
    return Vortex<Medium>::p_rel * pow(2, 2 * Vortex<Medium>::m + 1) * alglib::gammafunction(Vortex<Medium>::m + 1) *
    alglib::gammafunction(Vortex<Medium>::m + 2) / (2 * alglib::gammafunction(2 * Vortex<Medium>::m + 1)) *
    Vortex<Medium>::calculate_p_g();
}


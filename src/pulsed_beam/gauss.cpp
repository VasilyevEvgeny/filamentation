//
// Created by vasilyev on 04.07.2019.
//

#include "gauss.h"

template<typename Medium>
Gauss<Medium>::Gauss(Medium medium,
                     double _lambda_0,
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

    Gauss<Medium>::info = "gauss";


    Gauss<Medium>::p_cr_to_p_g = Gauss<Medium>::calculate_p_cr_to_p_g();
    Gauss<Medium>::p_0 = BasePulsedBeam<Medium>::calculate_p_0();

    Gauss<Medium>::i_0 = BasePulsedBeam<Medium>::calculate_i_0();

    BasePulsedBeam<Medium>::initialize_field();



}

template<typename Medium>
Gauss<Medium>::~Gauss() = default;


template<typename Medium>
double Gauss<Medium>::calculate_p_cr_to_p_g() {
    return 1.0;
}



template class Gauss<SiO2>;
template class Gauss<CaF2>;
template class Gauss<LiF>;

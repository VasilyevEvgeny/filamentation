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
                     double _p_rel) : BasePulsedBeam<Medium>(medium,
                                                             _lambda_0,
                                                             _r_0,
                                                             _n_r,
                                                             _t_0,
                                                             _n_t,
                                                             _p_rel) {

    Gauss<Medium>::info = "gauss";

    Gauss<Medium>::p_0 = Gauss<Medium>::calculate_p_0();

}

template<typename Medium>
Gauss<Medium>::~Gauss() = default;


template class Gauss<SiO2>;
template class Gauss<CaF2>;
template class Gauss<LiF>;

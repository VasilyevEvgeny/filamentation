//
// Created by vasilyev on 04.07.2019.
//

#ifndef FILAMENTATION_VORTEX_H
#define FILAMENTATION_VORTEX_H

#include "base_pulsed_beam.h"

template<typename Medium>
class Vortex : public BasePulsedBeam<Medium> {
public:
    Vortex(Medium medium,
           double _lambda_0,
           size_t _M,
           size_t _m,
           double _r_0,
           size_t _n_r,
           double _t_0,
           size_t _n_t,
           double _p_rel);

    ~Vortex() override;


    double calculate_p_0() override;

};

#endif //FILAMENTATION_VORTEX_H

//
// Created by vasilyev on 04.07.2019.
//

#ifndef FILAMENTATION_RING_H
#define FILAMENTATION_RING_H


#include "base_pulsed_beam/base_pulsed_beam.h"

template<typename Medium>
class Ring : public BasePulsedBeam<Medium> {
public:
    Ring();
    Ring(Medium medium,
          double _lambda_0,
          size_t _M,
          double _r_0,
          size_t _n_r,
          double _t_0,
          size_t _n_t,
          double _p0_to_p_cr);

    ~Ring() override;


    double calculate_p_cr_to_p_g() override;
};

#endif //FILAMENTATION_RING_H

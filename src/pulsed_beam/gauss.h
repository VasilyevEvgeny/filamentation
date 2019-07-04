//
// Created by vasilyev on 04.07.2019.
//

#ifndef FILAMENTATION_GAUSS_H
#define FILAMENTATION_GAUSS_H

#include "base_pulsed_beam.h"

template<typename Medium>
class Gauss : public BasePulsedBeam<Medium> {
public:
    Gauss(Medium medium,
          double _lambda_0,
          double _r_0,
          size_t _n_r,
          double _t_0,
          size_t _n_t,
          double _p_rel);

    ~Gauss() override;




};


#endif //FILAMENTATION_GAUSS_H

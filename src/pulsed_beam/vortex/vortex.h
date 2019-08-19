//
// Created by vasilyev on 04.07.2019.
//

#ifndef FILAMENTATION_VORTEX_H
#define FILAMENTATION_VORTEX_H

#include "pulsed_beam/base_pulsed_beam.h"

template<typename Medium>
class Vortex : public BasePulsedBeam<Medium> {
public:
    Vortex();
    explicit Vortex(std::shared_ptr<Medium> _medium,
                    double _lambda_0,
                    size_t _M,
                    size_t _m,
                    double _r_0,
                    size_t _n_r,
                    double _t_0,
                    size_t _n_t,
                    double _p0_to_p_cr);

    ~Vortex() override;

    double calculate_p_cr_to_p_g() override;

};




#endif //FILAMENTATION_VORTEX_H

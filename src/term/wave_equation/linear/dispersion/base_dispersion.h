//
// Created by vasilyev on 23.07.2019.
//

#ifndef FILAMENTATION_DISPERSIONEXECUTOR_H
#define FILAMENTATION_DISPERSIONEXECUTOR_H

#include "term/wave_equation/linear/base_linear_term.h"


class BaseDispersion : public BaseLinearTerm {
public:
    BaseDispersion();
    explicit BaseDispersion(std::shared_ptr<BasePulsedBeam>& _pulsed_beam, bool _T);

    ~BaseDispersion();

};


#endif //FILAMENTATION_DISPERSIONEXECUTOR_H

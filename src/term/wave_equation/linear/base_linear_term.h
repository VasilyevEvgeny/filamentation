//
// Created by vasilyev on 27.07.2019.
//

#ifndef FILAMENTATION_BASELINEARTERM_H
#define FILAMENTATION_BASELINEARTERM_H

#include "term/base_term.h"

class BaseLinearTerm : public BaseTerm {
public:
    BaseLinearTerm();
    explicit BaseLinearTerm(std::shared_ptr<BasePulsedBeam>& _pulsed_beam, bool _T);

    virtual ~BaseLinearTerm();

    virtual void process(double dz) = 0;
};


#endif //FILAMENTATION_BASELINEARTERM_H

//
// Created by vasilyev on 11.07.2019.
//

#ifndef FILAMENTATION_BASETERM_H
#define FILAMENTATION_BASETERM_H

#include "pulsed_beam/base_pulsed_beam.h"
#include "pulsed_beam/gauss/gauss.h"
#include "pulsed_beam/ring/ring.h"
#include "pulsed_beam/vortex/vortex.h"
#include "medium/material/base_medium.h"
#include "medium/material/SiO2/SiO2.h"
#include "medium/material/CaF2/CaF2.h"
#include "medium/material/LiF/LiF.h"


class BaseTerm {
public:
    BaseTerm();
    explicit BaseTerm(std::shared_ptr<BasePulsedBeam>& _pulsed_beam,
                      bool _T);
    virtual ~BaseTerm();

    std::shared_ptr<BasePulsedBeam> pulsed_beam;

    bool T;

    std::string name;
    std::string formula;

};


#endif //FILAMENTATION_BASETERM_H

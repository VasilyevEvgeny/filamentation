//
// Created by vasilyev on 28.06.2019.
//

#ifndef FILAMENTATION_PROPAGATOR_H
#define FILAMENTATION_PROPAGATOR_H

#include "PulsedBeam.h"

class Propagator {
public:
    explicit Propagator(PulsedBeam &_pulsed_beam);
    ~Propagator();


private:
    PulsedBeam pulsed_beam;

};


#endif //FILAMENTATION_PROPAGATOR_H

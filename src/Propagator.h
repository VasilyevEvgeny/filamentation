//
// Created by vasilyev on 28.06.2019.
//

#ifndef FILAMENTATION_PROPAGATOR_H
#define FILAMENTATION_PROPAGATOR_H

#include <map>
#include <string>

#include "PulsedBeam.h"

class Propagator {
public:
    explicit Propagator(
            PulsedBeam &_pulsed_beam,
            std::map<std::string, std::string>& args);
    ~Propagator();


private:
    PulsedBeam pulsed_beam;

};


#endif //FILAMENTATION_PROPAGATOR_H

//
// Created by vasilyev on 28.06.2019.
//

#ifndef FILAMENTATION_PROPAGATOR_H
#define FILAMENTATION_PROPAGATOR_H

#include <map>
#include <string>

#include "PulsedBeam.h"
#include "Logger.h"
#include "medium/medium.h"

class Propagator {
public:
    Propagator(std::map<std::string, std::string>& args, PulsedBeam &_pulsed_beam);
    ~Propagator();


private:
    PulsedBeam pulsed_beam;

};


#endif //FILAMENTATION_PROPAGATOR_H

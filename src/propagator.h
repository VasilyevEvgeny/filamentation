//
// Created by vasilyev on 28.06.2019.
//

#ifndef FILAMENTATION_PROPAGATOR_H
#define FILAMENTATION_PROPAGATOR_H

#include <map>
#include <string>

#include "pulsed_beam.h"
#include "logger.h"
#include "medium/base_medium.h"

template <typename Medium> class Propagator {
public:
    Propagator(std::map<std::string, std::string>& args, PulsedBeam<Medium> &_pulsed_beam);
    ~Propagator();


private:
    PulsedBeam<Medium> pulsed_beam;

};


#endif //FILAMENTATION_PROPAGATOR_H

//
// Created by vasilyev on 28.08.2019.
//

#include <vector>
#include <omp.h>
#include <map>

#include "gtest/gtest.h"
#include "logger/logger.h"
#include "pulsed_beam/base_pulsed_beam.h"
#include "manager/config_manager/config_manager.h"
#include "propagator/propagator.h"
#include "misc/misc.h"


int main() {
    // config_manager
    ConfigManager config_manager(std::string("test/plasma/test_plasma_config.yml"));
    
    // postprocessor
    auto postprocessor = std::make_shared<Postprocessor>(config_manager);

    // propagator
    auto propagator = std::make_shared<Propagator>(config_manager,
                                                   postprocessor);

    // propagate!
    propagator->propagate();
}

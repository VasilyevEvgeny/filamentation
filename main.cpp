#include <iostream>
#include <fstream>
#include <sstream>
#include <omp.h>
#include <map>
#include <string>
#include <memory>

#include "logger/logger.h"
#include "pulsed_beam/base_pulsed_beam.h"
#include "manager/config_manager/config_manager.h"
#include "propagator/propagator.h"


int main(int argc, char** argv) {

    ConfigManager config_manager(std::string("config.yml"));

    auto postprocessor = std::make_shared<Postprocessor>(config_manager);

    auto propagator = std::make_shared<Propagator>(config_manager,
                                                   postprocessor);

    propagator->propagate();


    return 0;
}

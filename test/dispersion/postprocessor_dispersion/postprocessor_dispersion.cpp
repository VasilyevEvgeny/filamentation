//
// Created by vasilyev on 21.08.2019.
//

#include "postprocessor_dispersion.h"

PostprocessorDispersion::PostprocessorDispersion() = default;

PostprocessorDispersion::PostprocessorDispersion(ConfigManager& _config_manager)
: Postprocessor(_config_manager) {

}

PostprocessorDispersion::~PostprocessorDispersion() = default;


void PostprocessorDispersion::go(DirManager& dir_manager, std::shared_ptr<Logger>& logger) {

    logger->add_propagation_event(std::string("postprocessing"));

    postprocess(dir_manager,
                logger,
                std::string("test_dispersion_plot"),
                std::string("processing/test/dispersion.py"),
                std::string("....plotting test_dispersion"));

}

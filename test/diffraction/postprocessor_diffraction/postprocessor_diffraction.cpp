//
// Created by vasilyev on 21.08.2019.
//

#include "postprocessor_diffraction.h"

PostprocessorDiffraction::PostprocessorDiffraction() = default;

PostprocessorDiffraction::PostprocessorDiffraction(ConfigManager& _config_manager)
: Postprocessor(_config_manager) {

}

PostprocessorDiffraction::~PostprocessorDiffraction() = default;


void PostprocessorDiffraction::go(DirManager& dir_manager, std::shared_ptr<Logger>& logger) {

    logger->add_propagation_event(std::string("postprocessing"));

    postprocess(dir_manager,
                logger,
                std::string("test_diffraction_plot"),
                std::string("processing/test/diffraction.py"),
                std::string("....plotting test_diffraction"));

}

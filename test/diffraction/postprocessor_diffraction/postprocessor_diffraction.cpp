//
// Created by vasilyev on 21.08.2019.
//

#include "postprocessor_diffraction.h"

PostprocessorDiffraction::PostprocessorDiffraction() = default;

PostprocessorDiffraction::PostprocessorDiffraction(ConfigManager& _config_manager,
                                                   DirManager& _dir_manager,
                                                   std::shared_ptr<Logger>& _logger)
: Postprocessor(_config_manager, _dir_manager, _logger) {

}

PostprocessorDiffraction::~PostprocessorDiffraction() = default;


void PostprocessorDiffraction::go() {

    logger->add_propagation_event(std::string("postprocessing"));

    postprocess(std::string("test_diffraction_plot"),
                std::string("processing/test/diffraction.py"),
                std::string("....plotting test_diffraction"));

}

//
// Created by vasilyev on 27.07.2019.
//

#include "base_executor.h"


BaseExecutor::BaseExecutor() = default;


BaseExecutor::BaseExecutor(std::shared_ptr<BasePulsedBeam>& _pulsed_beam,
                           std::shared_ptr<Logger>& _logger)
: pulsed_beam(_pulsed_beam)
, logger(_logger) {

}

BaseExecutor::~BaseExecutor() = default;

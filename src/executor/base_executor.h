//
// Created by vasilyev on 27.07.2019.
//

#ifndef FILAMENTATION_BASEEXECUTOR_H
#define FILAMENTATION_BASEEXECUTOR_H

#include <vector>
#include <string>
#include <memory>

#include "pulsed_beam/gauss/gauss.h"
#include "pulsed_beam/ring/ring.h"
#include "pulsed_beam/vortex/vortex.h"

#include "medium/material/SiO2/SiO2.h"
#include "medium/material/CaF2/CaF2.h"
#include "medium/material/LiF/LiF.h"


class BaseExecutor {
public:
    BaseExecutor();
    explicit BaseExecutor(std::shared_ptr<BasePulsedBeam>& _pulsed_beam,
                          std::shared_ptr<Logger>& _logger);
    virtual ~BaseExecutor();

    std::shared_ptr<BasePulsedBeam> pulsed_beam;

    std::shared_ptr<Logger> logger;

    virtual void execute(double& dz) = 0;
};


#endif //FILAMENTATION_BASE_EXECUTOR_H

//
// Created by vasilyev on 04.07.2019.
//

#ifndef FILAMENTATION_VORTEX_H
#define FILAMENTATION_VORTEX_H

#include "pulsed_beam/base_pulsed_beam.h"


class Vortex : public BasePulsedBeam {
public:
    Vortex();
    explicit Vortex(std::shared_ptr<BaseMedium>& _medium,
                    ConfigManager& _config_manager,
                    std::shared_ptr<Logger>& _logger);

    ~Vortex() override;

    double calculate_P_cr_to_P_G() override;

};


#endif //FILAMENTATION_VORTEX_H

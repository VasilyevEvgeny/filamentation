//
// Created by vasilyev on 04.07.2019.
//

#ifndef FILAMENTATION_RING_H
#define FILAMENTATION_RING_H


#include "pulsed_beam/base_pulsed_beam.h"


class Ring : public BasePulsedBeam {
public:
    Ring();
    explicit Ring(std::shared_ptr<BaseMedium>& medium,
                  ConfigManager& _config_manager,
                  std::shared_ptr<Logger>& _logger);

    ~Ring() override;


    double calculate_P_cr_to_P_G() override;
};


#endif //FILAMENTATION_RING_H

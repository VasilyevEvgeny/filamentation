//
// Created by vasilyev on 04.07.2019.
//

#ifndef FILAMENTATION_GAUSS_H
#define FILAMENTATION_GAUSS_H

#include "pulsed_beam/base_pulsed_beam.h"

class Gauss : public BasePulsedBeam {
public:
    Gauss();
    explicit Gauss(std::shared_ptr<BaseMedium>& _medium,
                   ConfigManager& _config_manager,
                   std::shared_ptr<Logger>& _logger);

    ~Gauss() override;

    double calculate_p_cr_to_p_g() override;

};


#endif //FILAMENTATION_GAUSS_H

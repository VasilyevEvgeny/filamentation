//
// Created by vasilyev on 02.07.2019.
//

#ifndef FILAMENTATION_SIO2_H
#define FILAMENTATION_SIO2_H

#include "medium/material/base_medium.h"

class SiO2 : public BaseMedium {
public:
    SiO2();
    explicit SiO2(ConfigManager& _config_manager, std::shared_ptr<Logger>& _logger);
    ~SiO2() override;

    void initialize_kerr_parameters() override;
    void initialize_ionization_parameters() override;

private:


};


#endif //FILAMENTATION_SIO2_H

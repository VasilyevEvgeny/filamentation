//
// Created by vasilyev on 02.07.2019.
//

#ifndef FILAMENTATION_CAF2_H
#define FILAMENTATION_CAF2_H

#include "medium/material/base_medium.h"

class CaF2 : public BaseMedium {
public:
    CaF2();
    explicit CaF2(ConfigManager& _config_manager, std::shared_ptr<Logger>& _logger);
    ~CaF2() override;

    void initialize_kerr_parameters() override;
    void initialize_ionization_parameters() override;

private:


};


#endif //FILAMENTATION_CAF2_H

//
// Created by vasilyev on 04.07.2019.
//
//
#include "gauss.h"


Gauss::Gauss() = default;


Gauss::Gauss(std::shared_ptr<BaseMedium>& _medium,
             ConfigManager& _config_manager,
             std::shared_ptr<Logger>& _logger)
: BasePulsedBeam(_medium,
                 _config_manager,
                 _logger) {

    info = "gauss";

    logger->add_propagation_event(std::string("....calculating initial parameters in pulsed_beam"));

    P_cr_to_P_G = calculate_P_cr_to_P_G();
    P_0 = calculate_P_0();
    I_0 = calculate_I_0();
    E_0 = calculate_E_0();

    logger->add_propagation_event(std::string("....initialization of field in pulsed_beam"));
    initialize_field();

}

Gauss::~Gauss() = default;


double Gauss::calculate_P_cr_to_P_G() {
    return 1.0;
}


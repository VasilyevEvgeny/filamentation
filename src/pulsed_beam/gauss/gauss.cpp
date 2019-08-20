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

    p_cr_to_p_g = calculate_p_cr_to_p_g();
    p_0 = calculate_p_0();
    i_0 = calculate_i_0();
    e_0 = calculate_e_0();

    logger->add_propagation_event(std::string("....initialization of field in pulsed_beam"));
    initialize_field();

}

Gauss::~Gauss() = default;


double Gauss::calculate_p_cr_to_p_g() {
    return 1.0;
}


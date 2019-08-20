//
// Created by vasilyev on 04.07.2019.
//

#include "ring.h"


Ring::Ring() = default;


Ring::Ring(std::shared_ptr<BaseMedium>& _medium,
           ConfigManager& _config_manager,
           std::shared_ptr<Logger>& _logger)
: BasePulsedBeam(_medium,
                 _config_manager,
                 _logger) {

    info = "ring";

    M = _config_manager.M;

    logger->add_propagation_event(std::string("....calculating initial parameters in pulsed_beam"));

    p_cr_to_p_g = calculate_p_cr_to_p_g();
    p_0 = calculate_p_0();
    i_0 = calculate_i_0();
    e_0 = calculate_e_0();

    logger->add_propagation_event(std::string("....initialization of field in pulsed_beam"));
    initialize_field();

}


Ring::~Ring() = default;


double Ring::calculate_p_cr_to_p_g() {
    return 0.120 * Ring::M + 1.012;
}


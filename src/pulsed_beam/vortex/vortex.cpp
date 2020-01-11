//
// Created by vasilyev on 04.07.2019.
//

#include "vortex.h"


Vortex::Vortex() = default;


Vortex::Vortex(std::shared_ptr<BaseMedium>& _medium,
               ConfigManager& _config_manager,
               std::shared_ptr<Logger>& _logger)
: BasePulsedBeam(_medium,
                 _config_manager,
                 _logger) {

    info = "vortex";

    M = _config_manager.M;
    m = _config_manager.m;

    logger->add_propagation_event(std::string("....calculating initial parameters in pulsed_beam"));
    P_cr_to_P_G = calculate_P_cr_to_P_G();
    P_0 = calculate_P_0();
    I_0 = calculate_I_0();
    E_0 = calculate_E_0();

    logger->add_propagation_event(std::string("....initialization of field in pulsed_beam"));
    initialize_field();
}


Vortex::~Vortex() = default;


double Vortex::calculate_P_cr_to_P_G() {
    return pow(2, 2 * M + 1) * alglib::gammafunction(M + 1) *
           alglib::gammafunction(M + 2) / (2 * alglib::gammafunction(2 * M + 1));
}


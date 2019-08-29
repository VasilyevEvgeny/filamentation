//
// Created by vasilyev on 27.07.2019.
//

#include <chrono>
#include <algorithm>
#include <memory>

#include "linear_executor.h"
#include "misc/misc.h"



#define base BaseExecutor


LinearExecutor::LinearExecutor() = default;

LinearExecutor::LinearExecutor(std::shared_ptr<BasePulsedBeam>& _pulsed_beam,
                               ConfigManager& _config_manager,
                               std::shared_ptr<Logger>& _logger)
: BaseExecutor(_pulsed_beam, _logger)
, config_manager(_config_manager) {

    logger->add_propagation_event(std::string("....creating linear executor"));

    preprocess_active_linear_terms();

    fft = FastFourierTransform(base::pulsed_beam);

    diffraction = std::make_shared<Diffraction>(base::pulsed_beam, config_manager.T.at("diffraction"));
    dispersion_full = std::make_shared<DispersionFull>(base::pulsed_beam, config_manager.T.at("dispersion"));
    dispersion_gvd_sweep = std::make_shared<DispersionGVD>(base::pulsed_beam);
    dispersion_gvd_sweep->set_mode(std::string("sweep"));
    dispersion_gvd_fft = std::make_shared<DispersionGVD>(base::pulsed_beam);
    dispersion_gvd_fft->set_mode(std::string("fft"));

    // container for linear terms
    terms_pool.insert(std::pair<std::string, std::shared_ptr<BaseLinearTerm>>(diffraction->name, diffraction));
    terms_pool.insert(std::pair<std::string, std::shared_ptr<BaseLinearTerm>>(dispersion_full->name, dispersion_full));
    terms_pool.insert(std::pair<std::string, std::shared_ptr<BaseLinearTerm>>(dispersion_gvd_sweep->name, dispersion_gvd_sweep));
    terms_pool.insert(std::pair<std::string, std::shared_ptr<BaseLinearTerm>>(dispersion_gvd_fft->name, dispersion_gvd_fft));
}


LinearExecutor::~LinearExecutor() = default;


void LinearExecutor::preprocess_active_linear_terms() {
    for(auto& linear_term_name : config_manager.active_linear_terms) {
        if (linear_term_name != "dispersion_gvd_sweep") {
            active_linear_terms_upd.push_back(linear_term_name);
        }
    }
}


void LinearExecutor::execute(double& dz) {

    auto t_start = TIME::now();
    fft.forward();
    auto t_end = TIME::now();
    logger->term_times["fft"] += logger->duration(t_start, t_end);

    for(auto& linear_term_name : active_linear_terms_upd) {

        t_start = TIME::now();
        terms_pool[linear_term_name]->process(dz);
        t_end = TIME::now();
        logger->term_times[linear_term_name] += logger->duration(t_start, t_end);
    }

    t_start = TIME::now();
    fft.backward();
    t_end = TIME::now();
    logger->term_times["fft"] += logger->duration(t_start, t_end);

    if (config_manager.dispersion_gvd_sweep) {
        t_start = TIME::now();
        terms_pool["dispersion_gvd_sweep"]->process(dz);
        t_end = TIME::now();
        logger->term_times["dispersion_gvd_sweep"] += logger->duration(t_start, t_end);
    }

}


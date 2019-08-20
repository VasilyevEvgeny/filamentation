//
// Created by vasilyev on 27.07.2019.
//

#include "linear_executor.h"


#define base BaseExecutor


LinearExecutor::LinearExecutor() = default;

LinearExecutor::LinearExecutor(ConfigManager& _config_manager,
                                std::shared_ptr<BasePulsedBeam>& _pulsed_beam)
: BaseExecutor(_pulsed_beam)
, config_manager(_config_manager) {

    fft = FastFourierTransform(base::pulsed_beam);

    diffraction = std::make_shared<Diffraction>(base::pulsed_beam, config_manager.T.at("diffraction"));
    dispersion_full = std::make_shared<DispersionFull>(base::pulsed_beam, config_manager.T.at("dispersion"));
    dispersion_gvd = std::make_shared<DispersionGVD>(base::pulsed_beam);

    // container for linear terms
    terms_pool.insert(std::pair<std::string, std::shared_ptr<BaseLinearTerm>>(diffraction->name, diffraction));
    terms_pool.insert(std::pair<std::string, std::shared_ptr<BaseLinearTerm>>(dispersion_full->name, dispersion_full));
    terms_pool.insert(std::pair<std::string, std::shared_ptr<BaseLinearTerm>>(dispersion_gvd->name, dispersion_gvd));

}


LinearExecutor::~LinearExecutor() = default;


void LinearExecutor::execute(double dz) {

    fft.forward();

    for(auto& linear_term_name : config_manager.active_linear_terms) {
        terms_pool[linear_term_name]->process(dz);
    }

    fft.backward();

}


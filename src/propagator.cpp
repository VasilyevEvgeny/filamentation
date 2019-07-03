//
// Created by vasilyev on 28.06.2019.
//

#include "propagator.h"
#include "manager.h"

template <typename Medium>
Propagator<Medium>::Propagator(std::map<std::string, std::string>& args, PulsedBeam<Medium> &_pulsed_beam):
          pulsed_beam(_pulsed_beam)
        {


    Manager manager(args);
    Logger<Medium> logger(pulsed_beam);



    logger.save_initial_parameters(manager.current_results_dir, true, false);

}

template <typename Medium>
Propagator<Medium>::~Propagator() = default;


template class Propagator<SiO2>;
template class Propagator<CaF2>;
template class Propagator<LiF>;
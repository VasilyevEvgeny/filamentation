//
// Created by vasilyev on 23.07.2019.
//

#include "base_dispersion.h"


BaseDispersion::BaseDispersion() = default;


BaseDispersion::BaseDispersion(
        std::shared_ptr<BasePulsedBeam>& _pulsed_beam,
        bool _T)
: BaseLinearTerm(_pulsed_beam, _T) {


}


BaseDispersion::~BaseDispersion() = default;



//
// Created by vasilyev on 27.07.2019.
//

#include "base_linear_term.h"

BaseLinearTerm::BaseLinearTerm() = default;


BaseLinearTerm::BaseLinearTerm(std::shared_ptr<BasePulsedBeam>& _pulsed_beam,
                               bool _T)
: BaseTerm(_pulsed_beam, _T) {

}

BaseLinearTerm::~BaseLinearTerm() = default;


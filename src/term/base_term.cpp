//
// Created by vasilyev on 11.07.2019.
//

#include "base_term.h"


BaseTerm::BaseTerm() = default;


BaseTerm::BaseTerm(std::shared_ptr<BasePulsedBeam>& _pulsed_beam, bool _T)
: pulsed_beam(_pulsed_beam)
, T(_T){
}


BaseTerm::~BaseTerm() = default;

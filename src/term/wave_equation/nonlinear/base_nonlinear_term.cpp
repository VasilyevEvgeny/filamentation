//
// Created by vasilyev on 25.07.2019.
//

#include "base_nonlinear_term.h"

BaseNonlinearTerm::BaseNonlinearTerm() = default;


BaseNonlinearTerm::BaseNonlinearTerm(std::shared_ptr<BasePulsedBeam>& _pulsed_beam,
                                     bool _T)
: BaseTerm(_pulsed_beam, _T)
, R_kerr_instant(0)
, R_kerr_instant_T(0)
, R_plasma(0)
, R_plasma_T(0)
, R_dissipation(0)
, R_bremsstrahlung(0)
, R_bremsstrahlung_T(0) {

}

BaseNonlinearTerm::~BaseNonlinearTerm() = default;


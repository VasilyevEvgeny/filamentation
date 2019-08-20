//
// Created by vasilyev on 25.07.2019.
//

#ifndef FILAMENTATION_BASENONLINEARTERM_H
#define FILAMENTATION_BASENONLINEARTERM_H

#include "term/base_term.h"

class BaseNonlinearTerm : public BaseTerm {
public:
    BaseNonlinearTerm();
    explicit BaseNonlinearTerm(std::shared_ptr<BasePulsedBeam>& _pulsed_beam, bool _T);

    virtual ~BaseNonlinearTerm();

    std::complex<double> R_kerr_instant;
    std::complex<double> R_kerr_instant_T;
    std::complex<double> R_plasma;
    std::complex<double> R_plasma_T;
    std::complex<double> R_dissipation;
    std::complex<double> R_bremsstrahlung;
    std::complex<double> R_bremsstrahlung_T;

};


#endif //FILAMENTATION_BASENONLINEARTERM_H

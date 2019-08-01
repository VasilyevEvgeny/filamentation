//
// Created by vasilyev on 25.07.2019.
//

#ifndef FILAMENTATION_BASENONLINEARTERM_H
#define FILAMENTATION_BASENONLINEARTERM_H

#include "../base_term.h"

template<typename T> class BaseNonlinearTerm;

template<template<typename, typename...> class PulsedBeam, typename Medium>
class BaseNonlinearTerm<PulsedBeam<Medium>> : public BaseTerm<PulsedBeam<Medium>> {
public:
    BaseNonlinearTerm();
    explicit BaseNonlinearTerm(PulsedBeam<Medium>* _pulsed_beam, bool _T);

    virtual ~BaseNonlinearTerm();

    std::complex<double> R_kerr_instant;
    std::complex<double> R_kerr_instant_T;
    std::complex<double> R_plasma;
    std::complex<double> R_plasma_T;
    std::complex<double> R_diss;
    std::complex<double> R_bremsstrahlung;
    std::complex<double> R_bremsstrahlung_T;

};


#endif //FILAMENTATION_BASENONLINEARTERM_H

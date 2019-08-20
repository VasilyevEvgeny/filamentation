//
// Created by vasilyev on 26.07.2019.
//

#ifndef FILAMENTATION_KERRINSTANT_H
#define FILAMENTATION_KERRINSTANT_H


#include "term/wave_equation/nonlinear/base_nonlinear_term.h"

//template<typename T> class Kerr;

//template<template<typename, typename...> class PulsedBeam, typename Medium>
class Kerr : public BaseNonlinearTerm {
public:
    Kerr();
    explicit Kerr(std::shared_ptr<BasePulsedBeam>& _pulsed_beam, std::map<std::string, bool>& _kerr_info, bool _T);

    std::map<std::string, bool> kerr_info;
    double g;

    ~Kerr();
};


#endif //FILAMENTATION_KERRINSTANT_H

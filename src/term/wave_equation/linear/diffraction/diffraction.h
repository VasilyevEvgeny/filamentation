//
// Created by vasilyev on 16.07.2019.
//

#ifndef FILAMENTATION_DIFFRACTION_H
#define FILAMENTATION_DIFFRACTION_H


#include "term/base_term.h"
#include "term/wave_equation/linear/base_linear_term.h"
#include "pulsed_beam/base_pulsed_beam.h"
#include "medium/material/base_medium.h"

class Diffraction : public BaseLinearTerm {
public:
    Diffraction();
    explicit Diffraction(std::shared_ptr<BasePulsedBeam>& _pulsed_beam, bool _T);

    ~Diffraction();

    void process(double dz) override;

};


#endif //FILAMENTATION_DIFFRACTION_H

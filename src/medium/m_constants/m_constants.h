//
// Created by vasilyev on 29.06.2019.
//

#ifndef FILAMENTATION_MATHCONSTANTS_H
#define FILAMENTATION_MATHCONSTANTS_H

#include <complex>

class MathConstants {
public:
    MathConstants();
    ~MathConstants();

    double h_bar;
    double c;
    double e;
    double m_e;
    double epsilon_0;
    double mu_0;
    std::complex<double> M_COMPLEX_I;
};






#endif //FILAMENTATION_MATHCONSTANTS_H

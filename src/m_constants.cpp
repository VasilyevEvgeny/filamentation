//
// Created by vasilyev on 29.06.2019.
//

#include "m_constants.h"

MathConstants::MathConstants() :
        h_bar(1.054571800e-34)
        , c(2.9979245799999954e8)
        , e(1.602176620898e-19)
        , m_e(9.1093829140e-31)
        , epsilon_0(8.85418781762039e-12)
        , M_COMPLEX_I(std::complex<double>(0.0, 1.0)){

}

MathConstants::~MathConstants() = default;

//
// Created by vasilyev on 28.07.2019.
//

#ifndef FILAMENTATION_BASE_IONIZATION_H
#define FILAMENTATION_BASE_IONIZATION_H


class BaseIonization {
public:
    BaseIonization();
    virtual ~BaseIonization();


    virtual double R(double i) = 0;
};


#endif //FILAMENTATION_BASE_IONIZATION_H

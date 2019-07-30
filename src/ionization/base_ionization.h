//
// Created by vasilyev on 28.07.2019.
//

#ifndef FILAMENTATION_BASE_IONIZATION_H
#define FILAMENTATION_BASE_IONIZATION_H

#include <string>

class BaseIonization {
public:
    BaseIonization();
    virtual ~BaseIonization();

    std::string name;

    virtual double R(double i) = 0;

    void make_ionization_table(std::string& path_to_ionization_tables_dir, std::string& medium_name, double lambda_0);

};


#endif //FILAMENTATION_BASE_IONIZATION_H

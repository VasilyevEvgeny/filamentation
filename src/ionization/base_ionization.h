//
// Created by vasilyev on 28.07.2019.
//

#ifndef FILAMENTATION_BASE_IONIZATION_H
#define FILAMENTATION_BASE_IONIZATION_H

#include <string>
#include <map>
#include <vector>

class BaseIonization {
public:
    BaseIonization();
    virtual ~BaseIonization();

    std::string name;

    size_t n_i;
    double i_start;
    double i_step;

    virtual double calculate_R(double i) = 0;

    std::vector<double> rates;
    double R(double i);


    std::string generate_ionization_table_name(std::string& medium_name, double lambda_0);
    void make_ionization_table(std::string& path_to_ionization_tables_dir);
    void process_ionization_table(std::map<std::string, std::string>& args,
                                  std::string& path_to_ionization_table);

    void initialize_ionization_table(std::map<std::string, std::string>& args,
                                     std::string& path_to_ionization_tables_dir,
                                     std::string& medium_name,
                                     double lambda_0);

};


#endif //FILAMENTATION_BASE_IONIZATION_H

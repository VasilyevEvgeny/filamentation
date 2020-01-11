//
// Created by vasilyev on 28.07.2019.
//

#ifndef FILAMENTATION_BASE_IONIZATION_H
#define FILAMENTATION_BASE_IONIZATION_H

#include <string>
#include <map>
#include <vector>
#include <memory>

#include "logger/logger.h"
#include "manager/config_manager/config_manager.h"

class BaseIonization {
public:
    BaseIonization();
    explicit BaseIonization(std::shared_ptr<Logger>& _logger);
    virtual ~BaseIonization();

    std::shared_ptr<Logger> logger;

    std::string name;

    size_t n_i;
    double i_start;
    double i_step;

    virtual double calculate_R(double i) = 0;

    std::vector<double> rates;
    double R(double i);

    std::string generate_ionization_table_name(std::string& medium_name, double lambda_0);
    void make_ionization_table(std::string& path_to_ionization_tables_dir);
    void plot_ionization_table(ConfigManager& config_manager,
                               std::string& path_to_ionization_table) const;

    void initialize_ionization_table(ConfigManager& config_manager,
                                     double lambda_0);

};


#endif //FILAMENTATION_BASE_IONIZATION_H

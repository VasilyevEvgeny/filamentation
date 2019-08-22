//
// Created by vasilyev on 22.08.2019.
//

#include <vector>
#include <omp.h>
#include <map>

#include "gtest/gtest.h"
#include "logger/logger.h"
#include "pulsed_beam/base_pulsed_beam.h"
#include "manager/config_manager/config_manager.h"
#include "propagator/propagator.h"
#include "postprocessor_dispersion/postprocessor_dispersion.h"
#include "misc/misc.h"


int main(int argc, char** argv) {

    // config_manager
    ConfigManager config_manager(std::string("test/dispersion/test_dispersion_config.yml"));

    // multidir_name
    std::string multidir_name = config_manager.prefix + "_" + get_current_datetime("dir_manager");

    // parameters
    std::vector<std::string> terms = {"dispersion_full", "dispersion_gvd_sweep", "dispersion_gvd_fft"};

    // main cycle
    for (auto& term_name : terms) {

        // current_results_dir_name
        config_manager.active_linear_terms = {term_name};
        config_manager.dispersion_gvd_sweep = (term_name == "dispersion_gvd_sweep");

        std::string current_results_dir_name = term_name;

        for (auto& term : config_manager.active_linear_terms) {
            std::cout << term << std::endl;
        }

        std::cout << config_manager.dispersion_gvd_sweep << std::endl;

        // postprocessor
        std::shared_ptr<Postprocessor> postprocessor = std::make_shared<PostprocessorDispersion>(config_manager);

        // propagator
        auto propagator = std::make_shared<Propagator>(config_manager,
                                                       postprocessor,
                                                       multidir_name,
                                                       current_results_dir_name);

        // corrections for test_diffraction
        propagator->dz = std::abs(propagator->pulsed_beam->z_disp) / propagator->n_z;

        // propagate!
        propagator->propagate();

        // delete
        postprocessor.reset();
        propagator.reset();
    }


    return 0;
}

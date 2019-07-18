#include <iostream>
#include <omp.h>
#include <map>
#include <string>
#include <omp.h>

#include "src/pulsed_beam/base_pulsed_beam/base_pulsed_beam.h"
#include "src/propagator.h"



std::map<std::string, std::string> parse_args(char **argv) {
     return  {{"prefix", argv[1]},
              {"path_to_project", argv[2]},
              {"global_root_dir", argv[3]},
              {"global_results_dir_name", argv[4]},
              {"python_interpreter", argv[5]},
              {"intensity_rt", argv[6]},
              {"track", argv[7]}};
}

//class MyClass {
//public:
//    explicit MyClass(int& _a) : a(_a) {
//        std::cout << "address of a in MyClass: " << &a << std::endl;
//    }
//    ~MyClass() = default;
//
//    int& a;
//
//};
//

int main(int argc, char** argv) {

//    int a = 25;
//    std::cout << "address of a in main: " << &a <<std::endl;
//
//    MyClass my_class(a);


    const size_t NUM_PROCS = omp_get_num_procs();

    std::cout << "NUM_PROCS: " << NUM_PROCS << std::endl;

    omp_set_num_threads(NUM_PROCS);

    auto args = parse_args(argv);

    double lambda_0 = 1800e-9;

    LiF medium(lambda_0);

    std::cout << "Address of medium in main: " << &medium << std::endl;

    Vortex<LiF> pulsed_beam(
            medium,
            lambda_0,
            1,
            1,
            100e-6,
            512,
            40e-15,
            1024,
            5);

    std::cout << "PULSED BEAM ADRESS IN MAIN: " << &pulsed_beam << std::endl;

    Propagator<Vortex<LiF>> propagator(
            args,
            pulsed_beam,
            1000,
            pulsed_beam.z_diff / 1000,
            10,
            0
            );

    propagator.propagate();


    return 0;
}
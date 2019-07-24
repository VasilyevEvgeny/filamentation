//
// Created by vasilyev on 18.07.2019.
//

#include "processor_diffraction.h"


ProcessorDiffraction::ProcessorDiffraction() = default;

ProcessorDiffraction::ProcessorDiffraction(std::map<std::string, std::string>& _args, Manager& _manager) :
Processor(_args, _manager){

    path_to_test_script = "/processing/test/diffraction.py";

}

ProcessorDiffraction::~ProcessorDiffraction() = default;



void ProcessorDiffraction::go() {

    std::string execute = path_to_python_interpreter + " " + path_to_project + path_to_test_script + " " +
                          "--current_results_dir=" + manager.current_results_dir;
    std::cout << execute << std::endl;
    std::system(execute.c_str());

}
cmake_minimum_required(VERSION 3.13)
project(filamentation)

set(CMAKE_CXX_STANDARD 14)

# added -fopenmp
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp -Werror")

#SET(CMAKE_CXX_COMPILER g++)
#SET(CMAKE_CXX_FLAGS "-lm -lfftw3")

#include_directories(reqg3g34)
#find_library(fftw lib/fftw/libfftw3-3)


add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)

include_directories(lib/alglib/src)

include_directories(src)
include_directories(test)

add_executable(filamentation
        # filamentation
        main.cpp

        src/pulsed_beam/base_pulsed_beam/base_pulsed_beam.cpp
        src/pulsed_beam/base_pulsed_beam/base_pulsed_beam.h
        src/pulsed_beam/base_pulsed_beam/parameters.cpp
        src/pulsed_beam/gauss.cpp
        src/pulsed_beam/gauss.h
        src/pulsed_beam/ring.cpp
        src/pulsed_beam/ring.h
        src/pulsed_beam/vortex.cpp
        src/pulsed_beam/vortex.h

        src/propagator.cpp
        src/propagator.h

        src/manager.cpp
        src/manager.h

        src/m_constants.cpp
        src/m_constants.h

        src/logger/logger.cpp
        src/logger/logger.h
        src/logger/initial_parameters_to_pdf.cpp
        src/logger/initial_parameters_to_yml.cpp

        src/medium/base_medium.cpp
        src/medium/base_medium.h
        src/medium/SiO2.cpp
        src/medium/SiO2.h
        src/medium/CaF2.cpp
        src/medium/CaF2.h
        src/medium/LiF.cpp
        src/medium/LiF.h

        src/processor.cpp
        src/processor.h
        test/diffraction/processor_diffraction.cpp
        test/diffraction/processor_diffraction.h
        test/dispersion/processor_dispersion.cpp
        test/dispersion/processor_dispersion.h

        src/term/base_term.cpp
        src/term/base_term.h

        src/fft/fft.cpp
        src/fft/fft.h

        src/term/wave_equation/linear/diffraction/diffraction.cpp
        src/term/wave_equation/linear/diffraction/diffraction.h

        src/term/wave_equation/linear/dispersion/base_dispersion.cpp
        src/term/wave_equation/linear/dispersion/base_dispersion.h
        src/term/wave_equation/linear/dispersion/dispersion_full.cpp
        src/term/wave_equation/linear/dispersion/dispersion_full.h
        src/term/wave_equation/linear/dispersion/dispersion_gvd.cpp
        src/term/wave_equation/linear/dispersion/dispersion_gvd.h


        # alglib
        lib/alglib/src/alglibinternal.cpp
        lib/alglib/src/alglibmisc.cpp
        lib/alglib/src/ap.cpp
        lib/alglib/src/dataanalysis.cpp
        lib/alglib/src/diffequations.cpp
        lib/alglib/src/fasttransforms.cpp
        lib/alglib/src/integration.cpp
        lib/alglib/src/interpolation.cpp
        lib/alglib/src/linalg.cpp
        lib/alglib/src/optimization.cpp
        lib/alglib/src/solvers.cpp
        lib/alglib/src/specialfunctions.cpp
        lib/alglib/src/statistics.cpp
        src/functions.cpp
        src/functions.h src/term/wave_equation/nonlinear/base_nonlinear_term.cpp src/term/wave_equation/nonlinear/base_nonlinear_term.h src/term/wave_equation/nonlinear/kerr/kerr.cpp src/term/wave_equation/nonlinear/kerr/kerr.h src/term/wave_equation/linear/base_linear_term.cpp src/term/wave_equation/linear/base_linear_term.h src/executor/base_executor.cpp src/executor/base_executor.h src/executor/linear_executor.cpp src/executor/linear_executor.h src/executor/nonlinear_executor.cpp src/executor/nonlinear_executor.h src/ionization/base_ionization.cpp src/ionization/base_ionization.h src/ionization/keldysh/base_keldysh.cpp src/ionization/keldysh/base_keldysh.h src/ionization/keldysh/original_keldysh.cpp src/ionization/keldysh/original_keldysh.h src/ionization/keldysh/smoothed_keldysh.cpp src/ionization/keldysh/smoothed_keldysh.h src/term/wave_equation/nonlinear/plasma/plasma.cpp src/term/wave_equation/nonlinear/plasma/plasma.h src/term/wave_equation/nonlinear/bremsstrahlung/bremsstrahlung.cpp src/term/wave_equation/nonlinear/bremsstrahlung/bremsstrahlung.h src/term/kinetic_equation/kinetic_equation.cpp src/term/kinetic_equation/kinetic_equation.h src/term/wave_equation/nonlinear/dissipation/dissipation.cpp src/term/wave_equation/nonlinear/dissipation/dissipation.h src/config_manager.cpp src/config_manager.h)

target_link_libraries(filamentation gtest gtest_main)
target_link_libraries(filamentation gmock gmock_main)


add_executable(test_diffraction

        test/diffraction/main.cpp
        test/diffraction/test_diffraction.cpp
        test/diffraction/test_diffraction.h

        src/pulsed_beam/base_pulsed_beam/base_pulsed_beam.cpp
        src/pulsed_beam/base_pulsed_beam/base_pulsed_beam.h
        src/pulsed_beam/base_pulsed_beam/parameters.cpp
        src/pulsed_beam/gauss.cpp
        src/pulsed_beam/gauss.h
        src/pulsed_beam/ring.cpp
        src/pulsed_beam/ring.h
        src/pulsed_beam/vortex.cpp
        src/pulsed_beam/vortex.h

        src/propagator.cpp
        src/propagator.h

        src/manager.cpp
        src/manager.h

        src/m_constants.cpp
        src/m_constants.h

        src/logger/logger.cpp
        src/logger/logger.h
        src/logger/initial_parameters_to_pdf.cpp
        src/logger/initial_parameters_to_yml.cpp

        src/medium/base_medium.cpp
        src/medium/base_medium.h
        src/medium/SiO2.cpp
        src/medium/SiO2.h
        src/medium/CaF2.cpp
        src/medium/CaF2.h
        src/medium/LiF.cpp
        src/medium/LiF.h

        src/processor.cpp
        src/processor.h
        test/diffraction/processor_diffraction.cpp
        test/diffraction/processor_diffraction.h
        test/dispersion/processor_dispersion.cpp
        test/dispersion/processor_dispersion.h

        src/term/base_term.cpp
        src/term/base_term.h

        src/fft/fft.cpp
        src/fft/fft.h

        src/term/wave_equation/linear/diffraction/diffraction.cpp
        src/term/wave_equation/linear/diffraction/diffraction.h

        src/term/wave_equation/linear/dispersion/base_dispersion.cpp
        src/term/wave_equation/linear/dispersion/base_dispersion.h
        src/term/wave_equation/linear/dispersion/dispersion_full.cpp
        src/term/wave_equation/linear/dispersion/dispersion_full.h
        src/term/wave_equation/linear/dispersion/dispersion_gvd.cpp
        src/term/wave_equation/linear/dispersion/dispersion_gvd.h


        # alglib
        lib/alglib/src/alglibinternal.cpp
        lib/alglib/src/alglibmisc.cpp
        lib/alglib/src/ap.cpp
        lib/alglib/src/dataanalysis.cpp
        lib/alglib/src/diffequations.cpp
        lib/alglib/src/fasttransforms.cpp
        lib/alglib/src/integration.cpp
        lib/alglib/src/interpolation.cpp
        lib/alglib/src/linalg.cpp
        lib/alglib/src/optimization.cpp
        lib/alglib/src/solvers.cpp
        lib/alglib/src/specialfunctions.cpp
        lib/alglib/src/statistics.cpp
        src/functions.cpp
        src/functions.h )


target_link_libraries(test_diffraction gtest gtest_main)
target_link_libraries(test_diffraction gmock gmock_main)


add_executable(test_dispersion

        test/dispersion/main.cpp
        test/dispersion/base_test_dispersion.cpp
        test/dispersion/base_test_dispersion.h
        test/dispersion/test_dispersion_full.cpp
        test/dispersion/test_dispersion_full.h

        src/pulsed_beam/base_pulsed_beam/base_pulsed_beam.cpp
        src/pulsed_beam/base_pulsed_beam/base_pulsed_beam.h
        src/pulsed_beam/base_pulsed_beam/parameters.cpp
        src/pulsed_beam/gauss.cpp
        src/pulsed_beam/gauss.h
        src/pulsed_beam/ring.cpp
        src/pulsed_beam/ring.h
        src/pulsed_beam/vortex.cpp
        src/pulsed_beam/vortex.h

        src/propagator.cpp
        src/propagator.h

        src/manager.cpp
        src/manager.h

        src/m_constants.cpp
        src/m_constants.h

        src/logger/logger.cpp
        src/logger/logger.h
        src/logger/initial_parameters_to_pdf.cpp
        src/logger/initial_parameters_to_yml.cpp

        src/medium/base_medium.cpp
        src/medium/base_medium.h
        src/medium/SiO2.cpp
        src/medium/SiO2.h
        src/medium/CaF2.cpp
        src/medium/CaF2.h
        src/medium/LiF.cpp
        src/medium/LiF.h

        src/processor.cpp
        src/processor.h
        test/diffraction/processor_diffraction.cpp
        test/diffraction/processor_diffraction.h
        test/dispersion/processor_dispersion.cpp
        test/dispersion/processor_dispersion.h

        src/term/base_term.cpp
        src/term/base_term.h

        src/fft/fft.cpp
        src/fft/fft.h

        src/term/wave_equation/linear/diffraction/diffraction.cpp
        src/term/wave_equation/linear/diffraction/diffraction.h

        src/term/wave_equation/linear/dispersion/base_dispersion.cpp
        src/term/wave_equation/linear/dispersion/base_dispersion.h
        src/term/wave_equation/linear/dispersion/dispersion_full.cpp
        src/term/wave_equation/linear/dispersion/dispersion_full.h
        src/term/wave_equation/linear/dispersion/dispersion_gvd.cpp
        src/term/wave_equation/linear/dispersion/dispersion_gvd.h


        # alglib
        lib/alglib/src/alglibinternal.cpp
        lib/alglib/src/alglibmisc.cpp
        lib/alglib/src/ap.cpp
        lib/alglib/src/dataanalysis.cpp
        lib/alglib/src/diffequations.cpp
        lib/alglib/src/fasttransforms.cpp
        lib/alglib/src/integration.cpp
        lib/alglib/src/interpolation.cpp
        lib/alglib/src/linalg.cpp
        lib/alglib/src/optimization.cpp
        lib/alglib/src/solvers.cpp
        lib/alglib/src/specialfunctions.cpp
        lib/alglib/src/statistics.cpp
        src/functions.cpp
        src/functions.h test/dispersion/test_dispersion_gvd.cpp test/dispersion/test_dispersion_gvd.h)


#find_library(lib/fftw/libfftw3-3.dll fftw)
#target_link_libraries(filamentation fftw3)
#target_link_libraries(mylib lib/fftw/libfftw3-3.dll)

#target_link_libraries(${PROJECT_NAME} lib/fftw/fftw)
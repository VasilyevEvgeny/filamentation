cmake_minimum_required(VERSION 3.13)
project(filamentation)

set(CMAKE_CXX_STANDARD 14)

# added -fopenmp
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp -Werror")

add_executable(
        # filamentation
        filamentation
        main.cpp

        src/pulsed_beam/base_pulsed_beam/base_pulsed_beam.cpp
        src/pulsed_beam/base_pulsed_beam/base_pulsed_beam.h
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

        src/medium/base_medium.cpp
        src/medium/base_medium.h
        src/medium/SiO2.cpp
        src/medium/SiO2.h
        src/medium/CaF2.cpp
        src/medium/CaF2.h
        src/medium/LiF.cpp
        src/medium/LiF.h


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

        src/pulsed_beam/base_pulsed_beam/parameters.cpp src/logger/initial_parameters_to_yml.cpp)
cmake_minimum_required(VERSION 3.13)
project(filamentation)

set(CMAKE_CXX_STANDARD 14)

# added -fopenmp
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp -Werror")

add_executable(filamentation main.cpp src/pulsed_beam.cpp src/pulsed_beam.h src/propagator.cpp src/propagator.h
        src/manager.cpp src/manager.h src/m_constants.cpp src/m_constants.h src/logger.cpp src/logger.h src/medium/base_medium.cpp src/medium/base_medium.h src/medium/SiO2.cpp src/medium/SiO2.h src/medium/CaF2.cpp src/medium/CaF2.h src/medium/LiF.cpp src/medium/LiF.h)
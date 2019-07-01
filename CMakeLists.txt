cmake_minimum_required(VERSION 3.13)
project(filamentation)

set(CMAKE_CXX_STANDARD 14)

# added -fopenmp
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp -Werror")

add_executable(filamentation main.cpp src/PulsedBeam.cpp src/PulsedBeam.h src/Propagator.cpp src/Propagator.h
        src/Manager.cpp src/Manager.h src/MathConstants.cpp src/MathConstants.h src/Logger.cpp src/Logger.h)
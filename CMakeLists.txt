cmake_minimum_required(VERSION 3.13)
project(filamentation)

set(CMAKE_CXX_STANDARD 17)

# added -fopenmp
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp")

add_executable(filamentation main.cpp)
cmake_minimum_required(VERSION 3.13)
project(GeneticAlgorithm)

set(CMAKE_CXX_STANDARD 14)

add_executable(GeneticAlgorithm main.cpp city.cpp city.hpp genetic_algorithm.cpp genetic_algorithm.hpp tour.cpp tour.hpp)
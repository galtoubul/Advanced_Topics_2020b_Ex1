cmake_minimum_required(VERSION 3.15)
project(Ex1)

set(CMAKE_CXX_STANDARD 14)

add_executable(Ex1 main.cpp ShipPlan.cpp ShipPlan.h Container.cpp Container.h ShipRoute.h ShipRoute.cpp Port.cpp Port.h Parser.cpp Parser.h Simulation.cpp Simulation.h StowageAlgorithm.cpp StowageAlgorithm.h)
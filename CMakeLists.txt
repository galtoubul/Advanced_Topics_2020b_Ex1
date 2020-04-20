cmake_minimum_required(VERSION 3.15)
project(Ex1)

set(CMAKE_CXX_STANDARD 17)

add_executable(Ex1 main.cpp ShipPlan.cpp ShipPlan.h Container.cpp Container.h Port.h Port.cpp ShipRoute.h ShipRoute.cpp
        Simulation.cpp Simulation.h Algorithm.cpp Algorithm.h main.h
        WeightBalanceCalculator.cpp WeightBalanceCalculator.h Parser.cpp Parser.h)

set(GCC_COVERAGE_COMPILE_FLAGS "-Wall -Wextra -Werror -pedantic-errors -DNDEBUG")
#SET(GCC_COVERAGE_LINK_FLAGS    "-lstdc++fs")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )
#SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")
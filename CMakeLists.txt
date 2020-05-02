cmake_minimum_required(VERSION 3.15)
project(Simulator)

set(CMAKE_CXX_STANDARD 17)

include_directories(../Algorithm)

add_executable(Simulator
        main.cpp
        ShipPlan.cpp ShipPlan.h
        Container.cpp Container.h
        Port.h Port.cpp
        ShipRoute.h ShipRoute.cpp
        Simulation.cpp Simulation.h
        WeightBalanceCalculator.cpp WeightBalanceCalculator.h
        Parser.cpp Parser.h
        ErrorsInterface.h
        ../Algorithm/AbstractAlgorithm.h
        ../Algorithm/_308394642_a.h ../Algorithm/_308394642_a.cpp)

set(GCC_COVERAGE_COMPILE_FLAGS "-Wall -Wextra -Werror -pedantic-errors -DNDEBUG")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )

target_link_libraries(Simulator)
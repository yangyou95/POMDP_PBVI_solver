cmake_minimum_required (VERSION 2.8)
set(CMAKE_CXX_STANDARD 11)
set(SOURCE 
Interface/AlphaVector.cpp 
Interface/Belief.cpp 
Parser/Parser.cpp
Planner/PbviPlanner.cpp
Problems/Tiger.cpp
Utils/Utils.cpp
)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/include)


SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

project (PBVI_Solver_Yang)
add_executable(PBVI PbviSolver.cpp ${SOURCE})
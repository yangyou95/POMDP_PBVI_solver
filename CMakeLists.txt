cmake_minimum_required (VERSION 2.8)
set(CMAKE_CXX_STANDARD 11)
set(SOURCE 
Interface/AlphaVector.cpp 
Interface/Belief.cpp 
Planner/PbviPlanner.cpp
Problems/Tiger.cpp
Utils/Utils.cpp
)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/include)

project (PBVI_Solver_Yang)
add_executable(PBVI PbviSolver.cpp ${SOURCE})
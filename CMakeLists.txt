cmake_minimum_required (VERSION 2.6)
project (PBVI_Solver_Yang)
add_executable(PBVI PbviSolver.cpp Belief.cpp Tiger.cpp Utils.cpp AlphaVector.cpp PbviPlanner.cpp)
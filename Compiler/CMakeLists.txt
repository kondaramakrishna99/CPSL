cmake_minimum_required(VERSION 2.8)

project(CPSL_Halide)

add_executable(CPSL_Halide cpsl.cpp Func.cpp Func.h Var.cpp Var.h Topology.cpp Topology.h)

target_link_libraries(CPSL_Halide

        )
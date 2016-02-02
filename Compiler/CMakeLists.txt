cmake_minimum_required(VERSION 2.8)

project(CPSL_Halide)

add_executable(CPSL_Halide cpsl.cpp Func.cpp Func.h Var.cpp Var.h Param.cpp Param.h Module.cpp Module.h CodeGen_C.cpp CodeGen_C.h Target.cpp Target.h Output.cpp Output.h)

target_link_libraries(CPSL_Halide

        )
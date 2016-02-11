cmake_minimum_required(VERSION 2.8)

project(CPSL_Halide)

add_executable(CPSL_Halide cpsl.cpp Func.cpp Func.h Var.cpp Var.h Param.cpp Param.h Module.cpp Module.h CodeGen_C.cpp CodeGen_C.h Target.cpp Target.h Output.cpp Output.h IR.cpp IR.h Expr.cpp Expr.h IROperator.cpp IROperator.h Schedule.cpp Schedule.h)

target_link_libraries(CPSL_Halide

        )
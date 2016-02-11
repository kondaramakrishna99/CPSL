/**
 * Describing Func as a basic block of the language.
 */

#ifndef DSLPROJECT_FUNC_H
#define DSLPROJECT_FUNC_H


#include "Var.h"
#include "Param.h"
#include "Target.h"
#include "Expr.h"

//Declarations, not relevant to this file. TODO: define a header file similar to halide
extern ExprNode operator+(Expr a, Expr b);

class Func { //TODO: More features needs to be added as we understand the domain.
    std::vector<Param> params;
    std::vector<ExprNode> exprs;

public:
    Func();
    Func(Param p1);
    void compile_to_c(std::string fName);
    void compile_to_c(std::string fName, Target t);
    void operator=(ExprNode e);

    template<class Var, class... Args>
    void operator() (Var t, Args... args);
    //void comp(T var, Args... args);

};


#endif //DSLPROJECT_FUNC_H

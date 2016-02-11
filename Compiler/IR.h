//
// Created by kazem on 07/02/16.
//

#ifndef DSLPROJECT_IR_H
#define DSLPROJECT_IR_H

#include "Expr.h"


struct Add:ExprNode{
    Expr op1,op2;

    static ExprNode make(Expr a, Expr b);

};


#endif //DSLPROJECT_IR_H

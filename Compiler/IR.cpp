//
// Created by kazem on 07/02/16.
//

#include "IR.h"

ExprNode Add::make(Expr a, Expr b) {

    Add node;

    node.op1 = a;
    node.op2 = b;
    return node;
}
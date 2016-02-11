//
// Created by kazem on 07/02/16.
//

#ifndef DSLPROJECT_IROPERATOR_H
#define DSLPROJECT_IROPERATOR_H

#include "Expr.h"
#include "IR.h"

ExprNode operator+(Expr a, Expr b){
    return Add::make(a,b);
}


#endif //DSLPROJECT_IROPERATOR_H

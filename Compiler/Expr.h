//
// Created by kazem on 07/02/16.
//

#ifndef DSLPROJECT_EXPR_H
#define DSLPROJECT_EXPR_H

template <class T>
class IRNode {

public:
    IRNode(){};

};

class ExprNode:IRNode<int>{

public:
    ExprNode():IRNode(){};
};


class Expr: ExprNode {

public:
    Expr():ExprNode(){};

};


#endif //DSLPROJECT_EXPR_H

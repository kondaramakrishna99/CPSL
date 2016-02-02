//
// Created by kazem on 01/02/16.
//

#ifndef DSLPROJECT_MODULE_H
#define DSLPROJECT_MODULE_H


#include <vector>
#include "Func.h"
#include "Target.h"

class Module {
    std::vector<Func> funcs;
    Target target;
    std::string mName;

public:
    Module();
    Module(std::string fName, Target target);
    void append(Func func);

};


#endif //DSLPROJECT_MODULE_H

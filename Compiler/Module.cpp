//
// Created by kazem on 01/02/16.
//

#include "Module.h"

Module::Module() {

}

Module::Module(std::string fName, Target t) {
    mName = fName;
    target = t;
}

void Module::append(Func func) {
    funcs.push_back(func);
}
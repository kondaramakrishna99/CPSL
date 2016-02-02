/**
 * This file generates C code for the given program
 */
#ifndef DSLPROJECT_CODEGEN_C_H
#define DSLPROJECT_CODEGEN_C_H


#include <iosfwd>
#include <fstream>
#include "Module.h"

class CodeGen_C { //TODO Defining IRPrinter and IRVisitor and inherite from them for this class
    std::ostream &outFile;
public:
    CodeGen_C();
    CodeGen_C(std::ostream& file);
    void compile(Module module);

};


#endif //DSLPROJECT_CODEGEN_C_H

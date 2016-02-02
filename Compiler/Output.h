/**
 * Stand-alone functions managing output related tasks.
 */

#ifndef DSLPROJECT_OUTPUT_H
#define DSLPROJECT_OUTPUT_H


#include <string>

#include "Module.h"

class Output {
public:
    static void compile_to_source_c(Module module, std::string fName);

};


#endif //DSLPROJECT_OUTPUT_H


#include <fstream>
#include "Output.h"
#include "CodeGen_C.h"


void Output::compile_to_source_c(Module module, std::string fName){
    std::ofstream file(fName+"_gen.cpp");
    CodeGen_C cg_c(file);
    cg_c.compile(module);
    file.close();
}


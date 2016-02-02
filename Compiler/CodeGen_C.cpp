

#include "CodeGen_C.h"


CodeGen_C::CodeGen_C(std::ostream& outfile):outFile(outfile){ }

    /** Because the language is very simple, the IR has only
    * one node i.e., state_estimation. Therefore, we generate
     * the code equal with this node
     */
void CodeGen_C::compile(Module module){
    //inserting headers ...
    outFile<<"#include<stdio>\n";
    outFile<<"#include <armadillo>\n";
    //Inserting main
    outFile<<"int main(){\n";
    //Creating matrixes and ...
    //generating code for Funs one-by-one.

    outFile<<"return 0;\n";
    outFile<<"}\n";

}

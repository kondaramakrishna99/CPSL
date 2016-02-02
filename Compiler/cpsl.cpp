/**
* Original CPSL code will be here
*/


#include <stdio.h>
#include "Func.h"


/// entry to our framework
int main(int argc, char *argv[]) {
    Case casem("case.m");
    Func state_estimation(casem);
    state_estimation.compile_to_c("c_source.cpp");

    printf("CPSL code generated, but not yet run.\n");
    return 0;
}

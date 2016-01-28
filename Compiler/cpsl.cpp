//------------------------------------------------------------------------------
// Original CPSL code
//------------------------------------------------------------------------------


#include <stdio.h>
#include "Func.h"
#include "Var.h"
#include "Topology.h"



/// entry to our framework
int main(int argc, char *argv[]) {
    // first, print the Copyright notice
    Func state_estimation;
    Var v, y;
    Topology t;
    //Measurement s; TODO
    // We might need to add a MATRIX type.
    //state_estimation(v) = op1(t,s); TODO
    state_estimation.compile_to_c();

    printf("CPSL code generated, but not yet run.\n");
    return 0;
}
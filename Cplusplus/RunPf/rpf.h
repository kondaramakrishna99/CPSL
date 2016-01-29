

#ifndef RPF_H
#define RPF_H

#include <cstdlib>
#include <iostream>
#include <armadillo>

using namespace std;
using namespace arma;
struct bus
{
    double BUS_I;       
    double BUS_TYPE;
    double PD;
    double QD;
    double GS;
    double BS;
    double BUS_AREA;
    double VM;
    double VA;
    double BASE_KV;
    double ZONE;
    double VMIN;
    double VMAX;
};

struct gen
{
    double GEN_BUS     ;
    double PG          ;
    double QG          ;
    double QMAX        ;
    double QMIN        ;
    double VG          ;
    double MBASE       ;
    double GEN_STATUS  ;
    double PMAX        ;
    double PMIN        ;
    double PC1         ;
    double PC2         ;
    double QC1MIN      ;
    double QC1MAX      ;
    double QC2MIN      ;
    double QC2MAX      ;
    double RAMP_AGC    ;
    double RAMP_10     ;
    double RAMP_30     ;
    double RAMP_Q      ;
    double APF         ;
};

struct branch
{
    double F_BUS    ; 
    double T_BUS    ; 
    double BR_R     ; 
    double BR_X     ; 
    double BR_B     ; 
    double RATE_A   ; 
    double RATE_B   ; 
    double RATE_C   ; 
    double TAP      ; 
    double SHIFT    ;
    double BR_STATUS;
    double ANGMIN   ;
    double ANGMAX   ;
};

extern vector<bus> buses;
extern vector<gen> gens;
extern vector<branch> branches;

extern mat bus_m;
 extern mat gen_m;
 extern mat branch_m;
 extern int baseMVA;
 
const int PQ      = 1;
const int PV      = 2;
const int REF     = 3;
const int NONE    = 4;

const int BUS_I       = 0;    // bus number (1 to 29997)
const int BUS_TYPE    = 1;    // bus type (1 - PQ bus, 2 - PV bus, 3 - reference bus, 4 - isolated bus)
const int PD          = 2;    // Pd, real power demand (MW)
const int QD          = 3;    // Qd, reactive power demand (MVAr)
const int GS          = 4;    // Gs, shunt conductance (MW at V = 1.0 p.u.)
const int BS          = 5;    // Bs, shunt susceptance (MVAr at V = 1.0 p.u.)
const int BUS_AREA    = 6;    // area number, 1-100
const int VM          = 7;    // Vm, voltage magnitude (p.u.)
const int VA          = 8;    // Va, voltage angle (degrees)
const int BASE_KV     = 9;   // baseKV, base voltage (kV)
const int ZONE        = 10;   // zone, loss zone (1-999)
const int VMAX        = 11;   // maxVm, maximum voltage magnitude (p.u.)      (not in PTI format)
const int VMIN        = 12;   // minVm, minimum voltage magnitude (p.u.)      (not in PTI format)
                    //
const int LAM_P       = 13;   // Lagrange multiplier on real power mismatch (u/MW)
const int LAM_Q       = 14;   // Lagrange multiplier on reactive power mismatch (u/MVAr)
const int MU_VMAX     = 15;   // Kuhn-Tucker multiplier on upper voltage limit (u/p.u.)
const int MU_VMIN     = 16;   // Kuhn-Tucker multiplier on lower voltage limit (u/p.u.)

const int GEN_BUS     = 0;    // bus number
const int PG          = 1;    // Pg, real power output (MW)
const int QG          = 2;    // Qg, reactive power output (MVAr)
const int QMAX        = 3;    // Qmax, maximum reactive power output at Pmin (MVAr)
const int QMIN        = 4;    // Qmin, minimum reactive power output at Pmin (MVAr)
const int VG          = 5;    // Vg, voltage magnitude setpoint (p.u.)
const int MBASE       = 6;    // mBase, total MVA base of this machine, defaults to baseMVA
const int GEN_STATUS  = 7;    // status, 1 - machine in service, 0 - machine out of service
const int PMAX        = 8;    // Pmax, maximum real power output (MW)
const int PMIN        = 9;   // Pmin, minimum real power output (MW)
const int PC1         = 10;   // Pc1, lower real power output of PQ capability curve (MW)
const int PC2         = 11;   // Pc2, upper real power output of PQ capability curve (MW)
const int QC1MIN      = 12;   // Qc1min, minimum reactive power output at Pc1 (MVAr)
const int QC1MAX      = 13;   // Qc1max, maximum reactive power output at Pc1 (MVAr)
const int QC2MIN      = 14;   // Qc2min, minimum reactive power output at Pc2 (MVAr)
const int QC2MAX      = 15;   // Qc2max, maximum reactive power output at Pc2 (MVAr)
const int RAMP_AGC    = 16;   // ramp rate for load following/AGC (MW/min)
const int RAMP_10     = 17;   // ramp rate for 10 minute reserves (MW)
const int RAMP_30     = 18;   // ramp rate for 30 minute reserves (MW)
const int RAMP_Q      = 19;   // ramp rate for reactive power (2 sec timescale) (MVAr/min)
const int APF         = 20;   // area participation factor

const int MU_PMAX     = 21;   // Kuhn-Tucker multiplier on upper Pg limit (u/MW)
const int MU_PMIN     = 22;   // Kuhn-Tucker multiplier on lower Pg limit (u/MW)
const int MU_QMAX     = 22;   // Kuhn-Tucker multiplier on upper Qg limit (u/MVAr)
const int MU_QMIN     = 23;   // Kuhn-Tucker multiplier on lower Qg limit (u/MVAr)

const int F_BUS       = 0;    // f, from bus number
const int T_BUS       = 1;    // t, to bus number
const int BR_R        = 2;    // r, resistance (p.u.)
const int BR_X        = 3;    // x, reactance (p.u.)
const int BR_B        = 4;    // b, total line charging susceptance (p.u.)
const int RATE_A      = 5;    // rateA, MVA rating A (long term rating)
const int RATE_B      = 6;    // rateB, MVA rating B (short term rating)
const int RATE_C      = 7;    // rateC, MVA rating C (emergency rating)
const int TAP         = 8;    // ratio, transformer off nominal turns ratio
const int SHIFT       = 9;   // angle, transformer phase shift angle (degrees)
const int BR_STATUS   = 10;   // initial branch status, 1 - in service, 0 - out of service
const int ANGMIN      = 11;   // minimum angle difference, angle(Vf) - angle(Vt) (degrees)
const int ANGMAX      = 12;   // maximum angle difference, angle(Vf) - angle(Vt) (degrees)

const int PF          = 13;   // real power injected at "from" bus end (MW)       (not in PTI format)
const int QF          = 14;   // reactive power injected at "from" bus end (MVAr) (not in PTI format)
const int PT          = 15;   // real power injected at "to" bus end (MW)         (not in PTI format)
const int QT          = 16;   // reactive power injected at "to" bus end (MVAr)   (not in PTI format)

const int MU_SF       = 17;   // Kuhn-Tucker multiplier on MVA limit at "from" bus (u/MVA)
const int MU_ST       = 18;   // Kuhn-Tucker multiplier on MVA limit at "to" bus (u/MVA)
const int MU_ANGMIN   = 19;   // Kuhn-Tucker multiplier lower angle difference limit (u/degree)
const int MU_ANGMAX   = 20;   // Kuhn-Tucker multiplier upper angle difference limit (u/degree)

#endif /* RPF_H */

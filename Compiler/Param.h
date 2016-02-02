/**
 * Param provides the information required for the functions.*NOT Precise enough YET*
 */
#ifndef DSLPROJECT_PARAM_H
#define DSLPROJECT_PARAM_H


#include <string>
#include <vector>


struct Bus
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

struct Gen
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

struct Branch
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

class Param {

public:
    Param();


};

class Case:public Param {
    std::vector<Bus> buses;
    std::vector<Gen> gens;
    std::vector<Branch> branches;
    std::string fName;
public:
    Case();
    Case(std::string fileName);
    void load();

};


#endif //DSLPROJECT_PARAM_H

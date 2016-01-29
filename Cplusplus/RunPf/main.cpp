#include <fstream>
#include <string.h>
#include <vector>
#include <armadillo>
#include <cstdlib>
#include <iostream>
#include "rpf.h"

using namespace std;
using namespace arma;

void loadcase();
void printBus(bus b);

uvec ref;
uvec pv;
uvec pq;
uvec genon; 
int main(int argc, char** argv) {
        loadcase();     // loading the case data into matrices
        cout.precision(6);
        ref = find(bus_m.col(BUS_TYPE)==REF );   // finding which bus is Ref,PV and PQ buses
        pq = find(bus_m.col(BUS_TYPE)==PQ );        
        pv = find(bus_m.col(BUS_TYPE)==PV);
        ref.print("REF");
        pv.print("PV: ");
        pq.print("PQ: ");
        
        genon = find(gen_m.col(GEN_STATUS)>0);      //finding which generators are on and which
        uvec colindex;                              //buses they are connected to.
        colindex << GEN_BUS;
        gen_m.submat(genon,colindex).print("GEN BUS NUM");
        
        colvec stat = branch_m.col(BR_STATUS);      
        stat.raw_print("STAT: ");                   //finding status of branches
        
        cx_mat sadmittance(branch_m.col(BR_R),branch_m.col(BR_X));
        sadmittance.raw_print("Serial admittance");     // finding sadmittance of each branch
        cx_colvec Ys = stat/sadmittance;
        Ys.raw_print("Ys");                           
        
        colvec Bc= stat%branch_m.col(BR_B);
        Bc.raw_print("Bc: ");
// ------------Finding Admittance Matrix -----------        
        int n1 = branch_m.n_rows;
        int nb = bus_m.n_rows;
        colvec tap(n1);
        tap.ones();
        tap.raw_print("TAP:");
        uvec i= find(branch_m.col(TAP)==0);
        i.raw_print("i: ");
        tap(i) = branch_m.col(TAP);
        tap.ones();                     // doubt here whether matpower is correct or not
        tap.raw_print("TAP ratios:");
        colvec z(n1);
        z.zeros();
        cx_vec temp_sh(z,branch_m.col(SHIFT));
        cx_vec tap1 =tap%exp(temp_sh);
        tap1.raw_print("TAP phase shift:");
        z.set_size((Bc.n_rows));
        cx_vec temp_Bc(z,Bc/2) ;
        cx_vec Ytt = Ys + temp_Bc;
        Ytt.raw_print("Ytt");
        cx_vec Yff= Ytt/(tap%conj(tap));
        Yff.raw_print("Yff");
        cx_vec Yft = -Ys/conj(tap);
        Yft.raw_print("Yft");
        cx_vec Ytf = -Ys/tap;
        Ytf.raw_print("Ytf");
        
        cx_vec Ysh(bus_m.col(GS),bus_m.col(BS));
        Ysh = Ysh/baseMVA;
        Ysh.raw_print("Ysh");
        
        
 // ------  building connection matrices-----------
        rowvec t = conv_to<rowvec>::from(branch_m.col(T_BUS));
        rowvec f = conv_to<rowvec>::from(branch_m.col(F_BUS));
        f.raw_print("f:");
        t.raw_print("t:");
        
        vec line1 =linspace<vec>(1,n1,n1);
        rowvec line = conv_to<rowvec>::from(line1);
        line.raw_print("line before:");
      
        mat locations1(line);
        locations1.insert_rows(1,f);
        locations1.raw_print("locations:");
        umat locations = conv_to<umat>::from(locations1);
        vec vals(n1);
        vals.ones();
        sp_mat Cf(locations,vals,true);
        Cf.raw_print("Cf");       
        
        locations1.shed_row(1);
        locations1.insert_rows(1,t);
        locations = conv_to<umat>::from(locations1);
        locations.raw_print("locations for Ct:");
        sp_mat Ct(locations,vals,true);
        Ct.raw_print("Ct");       
        
 // --------- building Yf and Yt i.e., complex current injections from and to bus
        line = join_rows(line,line);
        line.raw_print("line:");
        f= join_rows(f,t);
        f.raw_print("f:");
        
        mat locations2(line);
        locations2.insert_rows(1,f);
        locations = conv_to<umat>::from(locations2);
        locations.raw_print("locations");
        cx_vec vals1 = join_cols(Yff,Yft);
        vals1.raw_print("vals");
        cout<<"locations size"<<size(locations2)<<endl;
        cout<<"vals size"<<size(vals1)<<endl;
        sp_cx_mat Yf(locations,vals1,true);
        Yf.raw_print("Yf");       
        
        vals1 = join_cols(Ytf,Ytt);
        vals1.raw_print("vals");
        sp_cx_mat Yt(locations,vals1,true);
        Yt.raw_print("Yt");       
        
//-----------Build Ybus --------
        
        sp_mat temp1(size(Cf));
        temp1.zeros();
        sp_cx_mat Cf1(Cf.t(),temp1);
        sp_cx_mat Ct1(Ct.t(),temp1);
        Cf1.raw_print("Cf1:");
        Ct1.raw_print("Ct1:");
        
        vec line2 =linspace<vec>(1,nb,nb);
        rowvec line3 = conv_to<rowvec>::from(line2);
        line3.raw_print("line3 before:");
        mat locations3(line3);
        locations3.insert_rows(1,line3);
        locations3.raw_print("locations:");
        locations = conv_to<umat>::from(locations3);
        
        sp_cx_mat temp3(locations,Ysh,true);
        temp3.raw_print("temp3");       
        sp_cx_mat Ybus = Cf1*Yf + Ct1*Yt + temp3;
        Ybus.raw_print("Ybus");
        
//--------------Make Sbus -----------------------
        uvec on = find(gen_m.col(GEN_STATUS)>0);
        on.raw_print("On: ");
        uvec colindex1;
        colindex1 << GEN_BUS;
        vec gbus_t = gen_m.submat(on,colindex1);
        cout<<"gbus_t: "<<gbus_t<<" size: "<<size(gbus_t);
        rowvec gbus = conv_to<rowvec>::from(gbus_t);
        gbus.raw_print("Gbus: ");  
        
        int ngon = on.n_rows;
        vec ng_line_t =linspace<vec>(1,ngon,ngon);
       
        ng_line_t.raw_print("ng_line_t: ");
        rowvec ng_line = conv_to<rowvec>::from(ng_line_t);
        ng_line.raw_print("ng_line: ");
        
        mat locations_Cg(gbus);
        locations_Cg.insert_rows(1,ng_line);
        
        locations = conv_to<umat>::from(locations_Cg);
        locations.raw_print("locations:");
        
        vec ng_ones = ones<vec>(ngon);
        sp_mat Cg(locations,ng_ones,true);
        Cg.raw_print("Cg: ");
        cout <<"Cg: "<<size(Cg) <<" gbus: "<<size(gbus)<<endl; 
        sp_mat Cg_Sbus;
        Cg_Sbus = Cg.submat(1,1,Cg.n_rows-1,Cg.n_cols-1);
        Cg_Sbus.resize(nb,ngon);
        Cg_Sbus.raw_print("Cg Sbus: ");
        cout <<"Cg_Sbus: "<<size(Cg_Sbus) <<endl; 
        uvec pg_t;
        pg_t<<PG;
        mat gen_sbus_i = gen_m.submat(on,pg_t);
        gen_sbus_i.raw_print("i: ");
        cout<<"size i: "<<size(gen_sbus_i)<<endl;
        uvec qg_t;
        qg_t<<QG;
        mat gen_sbus_j = gen_m.submat(on,qg_t);
        gen_sbus_j.raw_print("j: ");
        cout<<"size j: "<<size(gen_sbus_j)<<endl;
        cx_mat gen_Sbus_t(gen_sbus_i,gen_sbus_j);
        gen_Sbus_t.raw_print("Gen Sbus t");
        cout<<"size t: "<<size(gen_Sbus_t)<<endl;
        
        cx_mat bus_Sbus_t(bus_m.col(PD),bus_m.col(QD));
        bus_Sbus_t.raw_print("bus_sbus_t: ");
        cout <<"Cg_Sbus: "<<size(Cg_Sbus) <<"gen_Sbus_t "<<size(gen_Sbus_t)<<endl; 
        mat zero_Sbus(Cg_Sbus.n_rows,Cg_Sbus.n_cols);
        zero_Sbus.zeros();
        mat Cg_Sbus_t1 = conv_to<mat>::from(Cg_Sbus);
        Cg_Sbus_t1.raw_print("Cg_Sbus_t1: ");
        cout<<"size Cg_Sbus_t1: "<< size(Cg_Sbus_t1)<<endl;
       cx_mat c_Cg_Sbus(Cg_Sbus_t1,zero_Sbus); 
        c_Cg_Sbus.raw_print("c_Cg_Sbus: ");
      //  cx_mat Sbus = c_Cg_Sbus*Cg_Sbus.t();
        //mat temp31 = real(gen_Sbus_t);
       // mat Sbus_real=Cg_Sbus_t1*gen_sbus_i;
        //Sbus_real.raw_print("Sbus real: ");
        return 0;
    }
    
    


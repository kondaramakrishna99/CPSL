#include <fstream>
#include <string.h>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <armadillo>
#include "rpf.h"

using namespace std;
using namespace arma;
vector<bus> buses;
vector<gen> gens;
vector<branch> branches;
 
 int bus_size=13;
 int gen_size=21;
 int branch_size=13;
 
 mat bus_m(1,1);
 mat gen_m(1,1);
 mat branch_m(1,1);
 int baseMVA;
 
 void printBus(bus b)
{
    cout<<"Bus Index " << b.BUS_I;       
    cout<<"	Type " <<b.BUS_TYPE;
    cout<<"	PD " <<b.PD;
    cout<<"	QD " <<b.QD;
    cout<<"	GS " <<b.GS;
    cout<<"	BS " <<b.BS;
    cout<<"	Area " <<b.BUS_AREA;
    cout<<"	VM " <<b.VM;
    cout<<"	VA " <<b.VA;
    cout<<"	Base_KV " <<b.BASE_KV;
    cout<<"	Zone " <<b.ZONE;
    cout<<"	Vmin " <<b.VMIN;
    cout<<"	Vmax " <<b.VMAX;
}

void printGen(gen g)
{
    cout<<"	GEN_BUS    " <<g.GEN_BUS   ;  
    cout<<"	PG         " <<g.PG        ;  
    cout<<"	QG         " <<g.QG        ;  
    cout<<"	QMAX       " <<g.QMAX      ;  
    cout<<"	QMIN       " <<g.QMIN      ;  
    cout<<"	VG         " <<g.VG        ;  
    cout<<"	MBASE      " <<g.MBASE     ;  
    cout<<"	GEN_STATUS " <<g.GEN_STATUS;  
    cout<<"	PMAX       " <<g.PMAX      ;  
    cout<<"	PMIN       " <<g.PMIN      ;  
    cout<<"	PC1        " <<g.PC1       ;  
    cout<<"	PC2        " <<g.PC2       ;  
    cout<<"	QC1MIN     " <<g.QC1MIN    ;  
    cout<<"	QC1MAX     " <<g.QC1MAX    ;  
    cout<<"	QC2MIN     " <<g.QC2MIN    ;  
    cout<<"	QC2MAX     " <<g.QC2MAX    ;  
    cout<<"	RAMP_AGC   " <<g.RAMP_AGC  ;  
    cout<<"	RAMP_10    " <<g.RAMP_10   ;  
    cout<<"	RAMP_30    " <<g.RAMP_30   ;  
    cout<<"	RAMP_Q     " <<g.RAMP_Q    ;  
    cout<<"	APF        " <<g.APF<<endl       ; 
}

void printBranch(branch br)
{
    	cout<<"  F_BUS     " << br.F_BUS    ;
        cout<<"  T_BUS     " << br.T_BUS    ;
        cout<<"  BR_R      " << br.BR_R     ;
        cout<<"  BR_X      " << br.BR_X     ;
        cout<<"  BR_B      " << br.BR_B     ;
        cout<<"  RATE_A    " << br.RATE_A   ;
        cout<<"  RATE_B    " << br.RATE_B   ;
        cout<<"  RATE_C    " << br.RATE_C   ;
        cout<<"  TAP       " << br.TAP      ;
        cout<<"  SHIFT     " << br.SHIFT    ;
        cout<<"  BR_STATUS " << br.BR_STATUS;
        cout<<"  ANGMIN    " << br.ANGMIN   ;
        cout<<"  ANGMAX    " << br.ANGMAX <<endl  ;
}


void loadcase()
{
    bus b1;
    string line1="";
    ifstream file;
    file.open("C:\\Users\\sravan\\Desktop\\case9.m");
    bool readBus=false;
    bool readGen=false;
    bool readBranch=false;
    
    if(file.is_open())
    {
        while(getline(file,line1))
        {
            char* line = new char[line1.length() + 1];
            strcpy(line, line1.c_str());
           // cout << line <<endl;
            if(line1.find("mpc.baseMVA")!=string::npos)
            {
                size_t index = line1.find("=");
                string num = line1.substr(index+1);
                char* temp = new char[num.length() + 1];
                strcpy(temp, num.c_str());
                baseMVA = atoi(temp);
                cout <<"baseMVA" << index <<" "<<num<<" "<<baseMVA;
            }
            if(line1.find("mpc.bus")!=string::npos)
            {
                //cout<<"found bus"<<endl;
                readBus=true;
            }
            if(line1.find("mpc.gen ")!=string::npos)
            {
                //cout<<"found gen"<<endl;
                readGen=true;
            }
            if(line1.find("mpc.branch")!=string::npos)
            {
                //cout<<"found branch"<<endl;
                readBranch=true;
            }
            if(line1.find("]")!=string::npos || line1.length()==0)
            {
                //cout<<" Done reading"<<endl;
                readBus=false;
                readBranch=false;
                readGen=false;
            }
            
            if(readBus ==true && line1.find("mpc.bus")==string::npos)
            {
                vector<double> words;
                char* word;
                int i=0;
                //cout << line <<endl;
                word = strtok(line, "\t");
                while(word!=NULL)
                {
                    //double k = atof(word[i]);
                  //  cout<<i<<": "<<word[i]<<" double: "<<k<<endl;     
                    words.push_back(atof(word));
                    i++;
                    word = strtok(NULL,"\t");
                    
                }
                bus b;
                b.BUS_I=words.at(0);       
                b.BUS_TYPE=words.at(1);
                b.PD=words.at(2);
                b.QD=words.at(3);
                b.GS=words.at(4);
                b.BS=words.at(5);
                b.BUS_AREA=words.at(6);
                b.VM=words.at(7);
                b.VA=words.at(8);
                b.BASE_KV=words.at(9);
                b.ZONE=words.at(10);
                b.VMIN=words.at(11);
                b.VMAX=words.at(12);
                //printBus(b);
                buses.push_back(b);
                words.clear();
            }
            
            
            if(readGen ==true && line1.find("mpc.gen ")==string::npos)
            {
                char* word;
                int i=0;
                vector<double> words;
                //cout << line <<endl;
                word = strtok(line, "\t");
                while(word!=NULL)
                {
                    //double k = atof(word[i]);
                    words.push_back(atof(word));
                    //cout<<i<<": "<<word<<" double: "<<words.at(i)<<endl;     
                    i++;
                    word = strtok(NULL,"\t");
                    
                }
                gen g;
                
                g.GEN_BUS=words.at(0);     
                g.PG=words.at(1);          
                g.QG=words.at(2);
                g.QMAX=words.at(3);        
                g.QMIN=words.at(4);        
                g.VG=words.at(5);          
                g.MBASE=words.at(6);       
                g.GEN_STATUS=words.at(7);  
                g.PMAX=words.at(8);        
                g.PMIN=words.at(9);        
                g.PC1=words.at(10);         
                g.PC2=words.at(11);         
                g.QC1MIN=words.at(12);      
                g.QC1MAX=words.at(13);      
                g.QC2MIN=words.at(14);      
                g.QC2MAX=words.at(15);      
                g.RAMP_AGC=words.at(16);    
                g.RAMP_10=words.at(17);     
                g.RAMP_30=words.at(18);     
                g.RAMP_Q=words.at(19);      
                g.APF=words.at(20);         
                
                gens.push_back(g);
            }
            
            if(readBranch ==true && line1.find("mpc.branch")==string::npos)
            {
                vector<double> words;
                char* word;
                int i=0;
                //cout << line <<endl;
                word = strtok(line, "\t");
                
                while(word!=NULL)
                {
                
                    words.push_back(atof(word));
                    //cout<<i<<": "<<word<<" double: "<<words.at(i)<<endl;     
                    i++;
                    word = strtok(NULL,"\t");
                    
                }
                branch br;
                br.F_BUS    =(int)words.at(0); 
                br.T_BUS    =words.at(1); 
                br.BR_R     =words.at(2); 
                br.BR_X     =words.at(3); 
                br.BR_B     =words.at(4); 
                br.RATE_A   =words.at(5); 
                br.RATE_B   =words.at(6); 
                br.RATE_C   =words.at(7); 
                br.TAP      =words.at(8); 
                br.SHIFT    =words.at(9);
                br.BR_STATUS=words.at(10);
                br.ANGMIN   =words.at(11);
                br.ANGMAX   =words.at(12);
                //printBus(b);
                branches.push_back(br);
                words.clear();
            }

        }
    }
    
        for(int i=0;i<buses.size();i++)
        {
           // cout<<i <<": "<<endl;
           // printBus(buses.at(i));
        }
        
        for(int i=0;i<gens.size();i++)
        {
           // cout<<i <<": "<<endl;
           // printGen(gens.at(i));
        }
        
        for(int i=0;i<branches.size();i++)
        {
            //cout<<i <<": "<<endl;
            //printBranch(branches.at(i));
        }
    
    bus_m.set_size(buses.size(),bus_size);
    gen_m.set_size(gens.size(),gen_size);
    branch_m.set_size(branches.size(),branch_size);
    
    for(int i=0;i<bus_m.n_rows;i++)
    {
        for(int j=0;j<bus_m.n_cols;j++)
        {
            bus b = buses.at(i);
            bus_m(i,0) = b.BUS_I;       
            bus_m(i,1) = b.BUS_TYPE;
            bus_m(i,2) = b.PD;
            bus_m(i,3) = b.QD;
            bus_m(i,4) = b.GS;
            bus_m(i,5) = b.BS;
            bus_m(i,6) = b.BUS_AREA;
            bus_m(i,7) = b.VM;
            bus_m(i,8) = b.VA;
            bus_m(i,9) = b.BASE_KV;
            bus_m(i,10)=  b.ZONE;
            bus_m(i,11)=  b.VMIN;
            bus_m(i,12)=  b.VMAX;
        }
    }
    cout.precision(4);
    bus_m.raw_print("BUSES: ");
  

    for(int i=0;i<gen_m.n_rows;i++)
    {
        for(int j=0;j<gen_m.n_cols;j++)
        {
            gen g = gens.at(i);
            gen_m(i,0)	= g.GEN_BUS;     
            gen_m(i,1)  =  g.PG;          
            gen_m(i,2)  =  g.QG;
            gen_m(i,3)  =  g.QMAX;        
            gen_m(i,4)  =  g.QMIN;        
            gen_m(i,5)  =  g.VG;          
            gen_m(i,6)  =  g.MBASE;       
            gen_m(i,7)  =  g.GEN_STATUS;  
            gen_m(i,8)  =  g.PMAX;        
            gen_m(i,9)  =  g.PMIN;        
            gen_m(i,10) =   g.PC1;         
            gen_m(i,11) =   g.PC2;         
            gen_m(i,12) =   g.QC1MIN;      
            gen_m(i,13) =   g.QC1MAX;      
            gen_m(i,14) =   g.QC2MIN;      
            gen_m(i,15) =   g.QC2MAX;      
            gen_m(i,16) =   g.RAMP_AGC;    
            gen_m(i,17) =   g.RAMP_10;     
            gen_m(i,18) =   g.RAMP_30;     
            gen_m(i,19) =   g.RAMP_Q;      
            gen_m(i,20) =   g.APF;         

        }
    }
    cout.precision(6);
    gen_m.raw_print("GENS: ");

    for(int i=0;i<branch_m.n_rows;i++)
    {
        for(int j=0;j<branch_m.n_cols;j++)
        {
            branch br = branches.at(i);
            branch_m(i,0)	=  br.F_BUS      ;
            branch_m(i,1)  =  br.T_BUS      ;
            branch_m(i,2)  =  br.BR_R       ;
            branch_m(i,3)  =  br.BR_X       ;
            branch_m(i,4)  =  br.BR_B       ;
            branch_m(i,5)  =  br.RATE_A     ;
            branch_m(i,6)  =  br.RATE_B     ;
            branch_m(i,7)  =  br.RATE_C     ;
            branch_m(i,8)  =  br.TAP        ;
            branch_m(i,9)  =  br.SHIFT      ;
            branch_m(i,10) =  br.BR_STATUS  ; 
            branch_m(i,11) =  br.ANGMIN     ; 
            branch_m(i,12) =  br.ANGMAX     ; 
            
        }
    }
    cout.precision(6);
    branch_m.raw_print("BRANCHES: ");
}



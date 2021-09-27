#ifndef __lib_h__
#define __lib_h__

#include"random.h"
#include <iostream>
#include <cstdlib>
#include <cmath>
#include<vector>
#include <fstream>

using namespace std;

//definisco una funzione per il calcolo dell'errore

double error ( vector <double> AV , vector <double> AV2 ,  int N){
    if(N==0){
        return 0 ;
    }

    double var = (AV2[N] - pow(AV[N], 2))/N ;
    return pow( var , 0.5) ;
};

void Set_Genny_up( Random &Genny ){
    int seed[4];
    int p1, p2;
    ifstream Primes("Primes");
    if (Primes.is_open()){
       Primes >> p1 >> p2 ;
    } else cerr << "PROBLEM: Unable to open Primes" << endl;
    Primes.close();

    ifstream input("seed.in");
    string property;
    if (input.is_open()){
       while ( !input.eof() ){
          input >> property;
          if( property == "RANDOMSEED" ){
             input >> seed[0] >> seed[1] >> seed[2] >> seed[3];
             Genny.SetRandom(seed,p1,p2);
          }
       }
       input.close();
    } else cerr << "PROBLEM: Unable to open seed.in" << endl;
}

#endif

#ifndef __lib_h__
#define __lib_h__

#include"random.h"
#include <iostream>
#include <cstdlib>
#include <cmath>
#include<fstream>
#include<vector>

using namespace std;

bool toss_needle( double l , Random &Genny ){

    double y_bar = Genny.Rannyu(0. , 1.); //genero un estremo della barretta

    //genero il seno di un angolo estratto uniformemente tra 0 e 2pi senza usare il valore di pi
    double u = Genny.Rannyu(-1. , 1.);
    double v = Genny.Rannyu(0 , 1.);
    while(pow(u , 2) + pow(v , 2) > 1){
        u = Genny.Rannyu(-1. , 1.);
        v = Genny.Rannyu(0 , 1.);
    }

    double sin_theta = 2. * u * v /(pow(u , 2) + pow(v , 2)) ;

    double y = y_bar + l*sin_theta ; //ricavo la coordinata y dell'altro estremo. (NB: le coordinate x sono inutili)

    if( ((y_bar < 1 && y > 1) || (y_bar > 1 && y < 1)) || ((y_bar > 1 && y > 1) || (y_bar > 0 && y < 0))  ) //mi basta una griglia con due righe verticali
        return true;                                                                                       //per riuscire a riprodurre un intero piano
    else
        return false;
};

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

#ifndef __lib_h__
#define __lib_h__

#include"random.h"
#include"integranda.h"
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <fstream>

using namespace std;

//definisco una funzione per il calcolo dell'errore

double error ( vector <double> AV , vector <double> AV2 ,  int N){
    if(N==0){
        return 0 ;
    }
    double var = (AV2[N] - pow(AV[N], 2))/N ;
    return pow( var , 0.5 ) ;
};

void set_random_gen( Random &ran_gen ){
    int seed[9];
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
             ran_gen.SetRandom(seed,p1,p2);
          }
       }
       input.close();
    } else cerr << "PROBLEM: Unable to open seed.in" << endl;
}

vector<double> metropolis_step( vector <double> pos , FunzioneBase&  p , Random& Genny , bool unif , bool gs){

    vector <double> newpos (3,0.);
    double step , var ;

    if ( gs == true ){ //ground state
        if ( unif == true ){ //T uniforme
            step = 1.2 ;
            newpos[0] = Genny.Rannyu( pos[0] - step , pos[0] + step) ;
            newpos[1] = Genny.Rannyu( pos[1] - step , pos[1] + step) ;
            newpos[2] = Genny.Rannyu( pos[2] - step , pos[2] + step) ;
            }
        else {//T gaussiana
            var = 0.75 ;
            newpos[0] = Genny.Gauss( pos[0] , var ) ;
            newpos[1] = Genny.Gauss( pos[1] , var ) ;
            newpos[2] = Genny.Gauss( pos[2] , var ) ;
        }
    }
    else{ //psi_210
        if ( unif == true ){ //T uniforme
            step = 3. ;
            newpos[0] = Genny.Rannyu( pos[0] - step , pos[0] + step ) ;
            newpos[1] = Genny.Rannyu( pos[1] - step , pos[1] + step ) ;
            newpos[2] = Genny.Rannyu( pos[2] - step , pos[2] + step ) ;
            }
        else { //T gaussiana
            var = 1.9 ;
            newpos[0] = Genny.Gauss( pos[0] , var ) ;
            newpos[1] = Genny.Gauss( pos[1] , var ) ;
            newpos[2] = Genny.Gauss( pos[2] , var ) ;
        }
    }

    double a = min( 1. , p.Eval(newpos)/ p.Eval(pos) ) ;

    if ( Genny.Rannyu(0. , 1.) < a ){
         return newpos;
    }
    else {
        return pos ;
    }

}


#endif

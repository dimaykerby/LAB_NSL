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

void set_random_gen( Random &ran ){
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
             ran.SetRandom(seed,p1,p2);
          }
       }
       input.close();
    } else cerr << "PROBLEM: Unable to open seed.in" << endl;
}

double Metropolis_step( double pos , FunzioneBase&  p , Random& Genny , double mu , double sigma){

    double newpos ;
    double step = 2.7 ;

    newpos = Genny.Rannyu( pos - step , pos + step ) ;

    double a = min( 1. , p.Eval( newpos , mu , sigma )*p.Eval(newpos , mu , sigma)/ (p.Eval(pos ,  mu , sigma) * p.Eval(pos , mu , sigma))  );

    if ( Genny.Rannyu() < a ){
         return newpos;
    }
    else {
        return pos ;
    }

}

double data_blocking(Random & Genny , FunzioneBase& myfunction , FunzioneBase& p , double mu , double sigma , int blocks, int L , bool fitting = false){

    double s ;
    double pos = Genny.Rannyu(-0.5 , 0.5) ;

    vector <double> sum_prog ( blocks , 0.);
    vector <double> sum_prog_2( blocks , 0.) ;
    vector <double> errors ( blocks , 0.) ;


    for( int i = 0 ; i < blocks ; i ++){
        s = 0. ;
        for( int j = 0 ; j < L ; j++){
            pos = Metropolis_step(  pos , p , Genny , mu , sigma ) ;
            s +=  myfunction.Eval( pos , mu , sigma );
         }
         s /= (double)L ;

         if (i==0){
             sum_prog[i] = s ;
             sum_prog_2[i] = pow(s , 2);
         }

          else {
              sum_prog[i] = sum_prog[i-1] + s ;
              sum_prog_2[i] = sum_prog_2[i-1] + pow(s , 2) ;
          }
      }

          for(int i = 0 ; i < blocks ; i++){
             sum_prog[i] /= (i+1) ;
             sum_prog_2[i] /= (i+1) ;
             errors[i] = error( sum_prog , sum_prog_2 , i );
         }

         if ( fitting == false ){
             ofstream out ;
             out.open("data.csv") ;

             for ( int i = 0 ; i < blocks ; i++ )
                out << sum_prog[ i ] << " , " << errors[ i ] << endl;

             out.close();
         }

    return sum_prog[blocks-1] ;
}


vector<double> fit_parameters( Random& Genny , FunzioneBase& myfunction, FunzioneBase& p  , double mu, double sigma ){
    double m , s ; //nuovi parametri
    double energy_old, energy_new ;
    int steps = pow(10 , 4) ;

    ofstream out;
    out.open("Parameters.csv");
    //out << mu << "," << sigma << endl ;

    for (int i = 0 ; i <= steps ; i++ ){

        m = Genny.Rannyu(0.75 , 0.85) ;
        s = Genny.Rannyu(0.55 , 0.68) ;

        energy_old = data_blocking(Genny , myfunction , p , mu , sigma , 20 , 1000 , true);
        energy_new = data_blocking(Genny , myfunction , p , m , s , 20 , 1000 , true );


        if ( energy_new < energy_old ){
            mu = m ;
            sigma = s;
        }

        if( i%50 == 0 ) {
            out << mu << "," << sigma << endl;
            cout << i << "/ 10000" << endl;
        }

    }

    return {mu , sigma};

}

#endif

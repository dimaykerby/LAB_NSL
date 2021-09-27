#include"random.h"
#include"lib.h"


#include<iostream>
#include<cmath>
#include<fstream>
#include<vector>

using namespace std;

int main(){

Random ran_gen ;
set_random_gen(ran_gen);

//densità di probabilità da campionare
psi_1 p ;
psi_2 q ;
vector <double> pos = { 1. , 0. , 0. } ;

int M = pow(10 , 7);
int nblocks = 100;
int L = int(M/nblocks) ;

cout << "Calcolo <r> per il ground state campionando uniformemente." << endl ;
bool unif = true , gs = true ;

vector <double> sum_prog ( nblocks , 0. );
vector <double> sum_prog_2( nblocks , 0. ) ;
vector <double> errors ( nblocks, 0. ) ;

double s = 0. ;
vector <double> oldpos (3 , 0.); //to estimate the acceptance probability
int accept = 0 ;

for( int i = 0 ; i < nblocks ; i ++){
    s = 0. ;
    for( int j = 0 ; j < L ; j++){
        oldpos = pos ;
        pos = metropolis_step( pos , p , ran_gen, unif , gs ) ;
        s += sqrt( (pos[0]*pos[0]) + (pos[1]*pos[1]) + (pos[2]*pos[2]) );
        if (oldpos != pos){
            accept ++;
        }
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

 cout << "Probabilità di accettazione: " << accept/(double)M << endl;

  for(int i = 0 ; i < nblocks ; i++){
      sum_prog[i] /= (i+1) ;
      sum_prog_2[i] /= (i+1) ;
      errors[i] = error( sum_prog , sum_prog_2 , i );
  }

ofstream out ;
out.open("ps1.csv") ;

  for ( int i = 0 ; i < nblocks ; i++ )
  	out << sum_prog[ i ] << " , " << errors[ i ] << endl;

fill(sum_prog.begin() , sum_prog.end() , 0.);
fill(sum_prog_2.begin() , sum_prog_2.end() , 0.);
fill(errors.begin() , errors.end() , 0.);


pos = {1. , 0. , 0.};
accept = 0 ;
unif = false ;
cout << "Calcolo <r> per il ground state campionando secondo una gaussiana." << endl ;

for( int i = 0 ; i < nblocks ; i ++){
    s = 0. ;
    for( int j = 0 ; j < L ; j++){
        oldpos = pos ;
        pos = metropolis_step( pos , p , ran_gen, unif , gs ) ;
        s += sqrt( pos[0]*pos[0] + pos[1]*pos[1] + pos[2]*pos[2] );
        if (oldpos != pos){
            accept ++;
        }
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

  cout << "Probabilità di accettazione: " << accept/(double)M << endl;

  for(int i = 0 ; i < nblocks ; i++){
      sum_prog[i] /= (i+1) ;
      sum_prog_2[i] /= (i+1) ;
      errors[i] = error( sum_prog , sum_prog_2 , i );
  }

  for ( int i = 0 ; i < nblocks ; i++ )
  	out << sum_prog[ i ] << " , " << errors[ i ] << endl;

out.close();

ofstream out2 ;
out2.open("ps2.csv") ;

fill(sum_prog.begin() , sum_prog.end() , 0.);
fill(sum_prog_2.begin() , sum_prog_2.end() , 0.);
fill(errors.begin() , errors.end() , 0.);

pos = {1. , 0. , 0.};
accept = 0 ;
unif = true ;
gs = false ;
cout << "Calcolo <r> per il primo stato eccitato campionando uniformemente." << endl ;

for( int i = 0 ; i < nblocks ; i ++){
    s = 0. ;
    for( int j = 0 ; j < L ; j++){
        oldpos = pos ;
        pos = metropolis_step( pos , q , ran_gen, unif , gs ) ;
        s += sqrt(pos[0]*pos[0] + pos[1]*pos[1] + pos[2]*pos[2]);
        if(oldpos != pos){
            accept ++ ;
        }
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

 cout << "Probabilità di accettazione: " << accept/(double)M << endl;

  for(int i = 0 ; i < nblocks ; i++){
      sum_prog[i] /= (i+1) ;
      sum_prog_2[i] /= (i+1) ;
      errors[i] = error( sum_prog , sum_prog_2 , i );
  }

  for ( int i = 0 ; i < nblocks ; i++ )
        out2 << sum_prog[ i ] << " , " << errors[ i ] << endl;

fill(sum_prog.begin() , sum_prog.end() , 0.);
fill(sum_prog_2.begin() , sum_prog_2.end() , 0.);
fill(errors.begin() , errors.end() , 0.);

pos = {1. , 0. , 0.};
unif = false ;
accept = 0;
cout << "Calcolo <r> per il primo stato eccitato campionando secondo una gaussiana." << endl ;


for( int i = 0 ; i < nblocks ; i ++){
    s = 0. ;
    for( int j = 0 ; j < L ; j++){
        oldpos = pos ;
        pos = metropolis_step( pos , q , ran_gen, unif , gs ) ;
        s += sqrt(pos[0]*pos[0] + pos[1]*pos[1] + pos[2]*pos[2]);
        if (oldpos!= pos){
            accept ++ ;
        }
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

cout << "Probabilità di accettazione: " << accept/(double)M << endl;

    for(int i = 0 ; i < nblocks ; i++){
        sum_prog[i] /= (i+1) ;
        sum_prog_2[i] /= (i+1) ;
        errors[i] = error( sum_prog , sum_prog_2 , i );
    }

    for ( int i = 0 ; i < nblocks ; i++ )
        out2 << sum_prog[ i ] << " , " << errors[ i ] << endl;

out2.close() ;

return 0 ;
}

#include"random.h"
#include"lib.h"

#include<iostream>
#include<cmath>
#include<fstream>
#include<vector>

using namespace std;

int main ( ) {

Random Genny;

//inizializzazione del generatore di numeri casuali
Set_Genny_up(Genny);

//stampo su file i risultati
ofstream out;
out.open( "data.csv" );

if(!out){
    cout << "Errore apertura file!\n" ;
    return -1;
}


vector <double> sum_prog ( N , 0.); // vector with N elements with 0 value
vector <double> sum_prog_2( N , 0.) ;
vector <double> errors ( N, 0.) ;

double s = 0. ;

for( int i = 0 ; i < N ; i ++){
    for( int j = 0 ; j < L; j++ ){ //L is the number of blocks
        s +=Genny.Rannyu(0. , 1) ;
    }
    s /= double(L) ;

    if (i==0){
      sum_prog[i] = s ;
      sum_prog_2[i] = pow(s , 2);
  }

  else {
      sum_prog[i] = sum_prog[i-1] + s ;
      sum_prog_2[i] = sum_prog_2[i-1] + pow(s , 2) ;
  }
  s = 0. ;
}

for(int i = 0 ; i < N ; i++){
  sum_prog[i] /= (i+1) ;
  sum_prog_2[i] /= (i+1) ;
  errors[i] = error( sum_prog , sum_prog_2 , i );
}


for ( int i = 0 ; i < N ; i++ )
out << sum_prog[ i ] << " , " << errors[ i ] << endl;

out.close();

return 0;
}

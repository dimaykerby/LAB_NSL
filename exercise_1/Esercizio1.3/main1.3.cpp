#include"random.h"
#include"lib.h"

#include<iostream>
#include<cmath>
#include<fstream>
#include<vector>

using namespace std;


int main(){

//Initializing the generator
Random Genny;
Set_Genny_up(Genny) ;

//setting parameters
double d = 1. ; //distanza tra le linee
double l = 0.8 ; //lunghezza barretta
int N_hit = 0 ;
double s = 0. ;


int M = pow(10 , 7); //Number of throws
int N = 100 ; //number of blocks

//Vectors for block's averages
vector<double> pi (N , 0.);
vector<double> pi_square (N , 0.);
vector<double> err (N , 0.);

for (int i = 0 ; i < N ; i++){

    for( int j = 0 ; j < M/N ; j++){
        if( toss_needle( l , Genny) ) //returns true or false whether the needle hit the bar or not
            N_hit ++ ;
    }

    s = 2*l*(M/N)/(double(N_hit)*d) ; //stima di pi nel blocco i

    if(i==0){
        pi[i] = s ;
        pi_square[i] = pow(s ,2) ;
    }
    else {
        pi[i] = pi[i-1] + s;
        pi_square[i] = pi_square[i-1] + pow( s , 2) ;
    }
    N_hit = 0 ;
}


for(int i = 0 ; i < N ; i++){
    pi[i] = pi[i]/(i+1);
    pi_square[i] = pi_square[i]/(i+1) ;
    err[i] = error(pi , pi_square , i);
}


//printing results
ofstream out;
    out.open( "data_pi.csv" );
    if(!out){
        cout << "Errore apertura file!\n" ;
        return -1;
    }

for ( int i = 0 ; i < N ; i++ )
	out << pi[ i ] << "," << err[i] << endl;

out.close();



return 0;
}

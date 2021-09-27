#include"random.h"
#include"lib.h"

#include<iostream>
#include<cmath>
#include<fstream>
#include<vector>

using namespace std;

int main(){

    Random Genny;

    //inizializzo il generatore
    Set_Genny_up(Genny) ;


    ofstream out;
    out.open( "dices.csv" );
    if(!out){
        cout << "Errore apertura file!\n" ;
        return -1;
    }

    // elementi sommati in S_N
    vector <int> N {1 , 2 , 10 , 100} ;


    double sum_unif = 0. ;
    double sum_exp = 0. ;
    double sum_lor = 0. ;


    for(int i = 0 ; i < N.size() ; i++){
        for(int k = 0 ; k < 10000 ; k++){ //10000 is the number of simulations
            for(int j = 0 ; j < N[i] ; j++){
                sum_unif += Genny.Rannyu(0. , 1);
                sum_exp += Genny.Exp(1.);
                sum_lor += Genny.Lorentz(1., 0.);
            }
            out << sum_unif/N[i] <<"," << sum_exp/N[i] << "," << sum_lor/N[i] << endl ;
            sum_unif =0.;
            sum_exp = 0.;
            sum_lor = 0. ;
        }
    }

    out.close();


    return 0;
};

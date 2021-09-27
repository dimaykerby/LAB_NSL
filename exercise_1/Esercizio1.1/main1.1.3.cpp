#include"random.h"
#include"lib.h"

#include<iostream>
#include<cmath>
#include<fstream>
#include<vector>

using namespace std;

int main ( ) {

Random Genny;

//inizializzo il seme
Set_Genny_up(Genny );

ofstream out;

out.open( "data_chi.csv" );
if(!out){
    cout << "Errore apertura file!\n" ;
    return -1;
}

int M = 100; //sottointervalli in (0,1)
int N = 10000; //numeri casuali generati
int expected = N/M ; //numero di eventi attesi in ogni sottointervallo
double chi_square = 0. ;
vector <int> counts(M , 0);

for( int i = 0 ; i < M ; i++){ //voglio fare 100 stime di chi, ognuna con N numeri casuali

    for(int j = 0 ; j < N ; j++)
        counts[floor(Genny.Rannyu(0. , 100))] += 1 ; //verifico in che subintervallo ricade il numero casuale generato
                                                        //floor(Genny.Rannyu(0. , 1.)*100) è un numero intero fra 0 e 100
    for(int k = 0 ; k < 100 ; k++)
        chi_square += pow(counts[k]-expected, 2) ; //definizione di chi quadro

    out << chi_square/expected << endl; //stampo su file
    chi_square = 0. ;
    fill(counts.begin() , counts.end() , 0); //svuoto il vettore
}

out.close();

return 0 ;

}

#include"random.h"
#include"lib.h"
#include "integranda.h"


#include<iostream>
#include<cmath>
#include<fstream>
#include <sstream>
#include<vector>

using namespace std;

int main(){

Random ran ;
set_random_gen(ran);

//funzione da integrare
integranda myfunction ;
psi p ;

//Parametri di partenza
double mu = 0.80 ;
double sigma = 0.65;

//Parameters for data blocking
int N = pow(10 , 6) ;
int blocks = 100 ;
int L = int(N/blocks); //stime per blocco:
double energy;

//Stimo l'energia con i parametri iniziali
energy = data_blocking(ran , myfunction , p , mu , sigma , blocks, L , true) ;
cout << "mu = " << mu << "\tsigma = " << sigma << "\tFirst energy estimate: " << energy << endl ;

//Cerco i parametri migliori
cout << "Finding the best parameters to minimize energy." <<endl ;
vector<double> opt = fit_parameters( ran , myfunction, p , mu, sigma ) ;
cout << "The best parameters are:\t" << "mu = " << opt[0] << "\tsigma = " << opt[1] << endl ;

//Ricalcolo l'energia con questi parametri
mu = opt[0];
sigma = opt[1];
energy = data_blocking(ran , myfunction , p , mu , sigma , blocks, L , false) ;
cout << "Final energy estimate: " << energy << endl ;

//Calcolo l'energia con tutte le configurazioni (mu, sigma) provate dalla
//funzione fit_parameters per poter poi fare un grafico 3D su python
cout << "Calculating energies for a 3D graph.." << endl;

vector<double> energies;
double temp , m , s ;
int i = 0 ;

ifstream in ;
in.open("Parameters.csv"); //Il file parameters.csv è generato dalla funzione fit_parameters
if (!in){
    cout<< "Unable to open file Parameters.csv" << endl ;
    return -1 ;
}

ofstream out;
out.open("Energies.csv");
if (!out){
    cout << "Unable to open Energies.csv "<< endl ;
    return -1 ;
}

string aux ;
vector <double> par ;
while( !in.eof() ){
    getline( in , aux ) ;

    stringstream ss( aux );
    while( ss.good() ){
        string substr ;
        getline( ss , substr , ',');
        par.push_back( std::stod( substr ) );
    }

    m = par[0] ;
    s = par[1] ;

    //cout << m << " , " << s << endl ;

    temp = data_blocking(ran , myfunction , p , m , s , blocks, L , true );
    par.clear();
    energies.push_back(temp) ;
    if (i%10==0) cout << i << " values calculated." << endl ;
    i++;
    if ( i == 201 ) break ;
}

for( int i = 0 ; i < energies.size() ; i++  ) out << energies[i] << endl;


out.close();

//Making the histogram

int sampled = pow(10 , 5);
double pos = 0.8 ; //starting point

ofstream out_histo ;
out_histo.open("psi.csv");
if (!out_histo) {
    cout << "Unable to open histo file." << endl;
    exit(-1);
}
for (int i = 0; i < sampled; i++) {
    pos = Metropolis_step (pos, p, ran , mu, sigma);
    out_histo << pos << endl;
}
out.close();

 return 0 ;
}

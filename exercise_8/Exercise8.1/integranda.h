#ifndef __Integranda_h__
#define __Integranda_h__

#include "funzionebase.h"


#include <cmath>
#include <vector>

using namespace std;

class psi : public FunzioneBase {

    public:
    psi() {};
    ~psi() {};

    double Eval( double x , double mu , double sigma ) const override { return exp(-pow((x-mu), 2)/ (2*sigma*sigma)) + exp(-pow((x+mu), 2)/ (2*sigma*sigma)); } ;

};


class integranda : public FunzioneBase {

    public:
    integranda () {};
    ~integranda() {};

    double Eval( double x , double mu , double sigma  ) const override {

        double psi = exp( -pow((x-mu), 2)/ (2*sigma*sigma) ) + exp( - pow((x+mu), 2)/ (2*sigma*sigma)) ;
        double kinetic_term = -0.5 * exp(-pow((x+mu), 2)/ (2*sigma*sigma)) * ( exp( 2*mu*x/(sigma*sigma) ) * (mu-sigma-x) * (mu+sigma-x) + pow( mu + x , 2 ) - (sigma*sigma) ) / pow(sigma , 4.);
        double potential_term = ( pow(x ,4) - 5./2. * pow( x , 2 ) ) * psi ;

        return ( kinetic_term + potential_term )/psi ; }

};



#endif

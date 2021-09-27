#ifndef __Integranda_h__
#define __Integranda_h__

#include "funzionebase.h"


#include <cmath>
#include <vector>

using namespace std;

class psi_1 : public FunzioneBase {

    public:
    psi_1 () {};
    ~psi_1() {};

    double Eval( vector<double> x ) const override { return 1 / M_PI * exp( - 2 * sqrt( x[0]*x[0] + x[1]*x[1] +x[2]*x[2] ) ); } ;

};

class psi_2 : public FunzioneBase {
    public:
        psi_2 () {};
        ~psi_2() {};

double Eval( vector<double> x ) const override { return 1 /( 32*M_PI )  * exp( - sqrt( x[0]*x[0] + x[1]*x[1] +x[2]*x[2] ) ) * pow(x[2],2) ; } ;
};



#endif

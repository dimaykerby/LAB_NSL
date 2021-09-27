#ifndef __funzionebase_h__
#define __funzionebase_h__

#include <vector>

using namespace std;


class FunzioneBase {

	public:
	virtual double Eval ( double x , double mu, double sigma ) const = 0;

};


#endif

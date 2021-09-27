#ifndef __funzionebase_h__
#define __funzionebase_h__

#include <vector>

using namespace std;


class FunzioneBase {

	public:
	virtual double Eval ( vector <double> x ) const = 0;

};


#endif

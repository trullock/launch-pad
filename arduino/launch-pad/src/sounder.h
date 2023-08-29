#ifndef Sounder_h
#define Sounder_h

#include "ISounder.h"

class Sounder : public ISounder
{
public:
	Sounder();
	~Sounder(){};
	virtual void silence();
	virtual void armed();
	virtual void passedContinuityTest();
	virtual void firing();

	bool pinAMode;
	bool pinBMode;
	bool pinCMode;
};

#endif
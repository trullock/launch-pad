#ifndef FiringMechanism_h
#define FiringMechanism_h

#include "IFiringMechanism.h"

class FiringMechanism : public IFiringMechanism
{
public:
	FiringMechanism();
	~FiringMechanism(){};
	virtual void fire();
	virtual void stopFiring();
};

#endif
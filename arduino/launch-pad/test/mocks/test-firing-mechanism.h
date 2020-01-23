#ifndef TestFiringMechanism_h
#define TestFiringMechanism_h

#include "../../IFiringMechanism.h"

class TestFiringMechanism : public IFiringMechanism
{
public:
	~TestFiringMechanism() { };
	virtual void fire();
	virtual void stopFiring ();
	void reset();
	bool wasFired;
};

#endif
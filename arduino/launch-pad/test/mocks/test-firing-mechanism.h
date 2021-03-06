#ifndef TestFiringMechanism_h
#define TestFiringMechanism_h

#include "../../src/IFiringMechanism.h"

class TestFiringMechanism : public IFiringMechanism
{
public:
	TestFiringMechanism();
	~TestFiringMechanism() { };
	virtual void fire();
	virtual void stopFiring ();
	void reset();
	bool wasFired;
	bool wasStopped;
};

#endif
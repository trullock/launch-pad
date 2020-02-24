#ifndef TestStateObserver_h
#define TestStateObserver_h

#include "../../src/IStateObserver.h"

class TestStateObserver : public IStateObserver
{
public:
	TestStateObserver();
	~TestStateObserver(){};
	virtual bool interlockEngaged();
	virtual bool firingMechanismEngaged();
	virtual float batteryVoltage();
	void setInterlockEngaged(bool engaged);
	void setFiringMechanismEngaged(bool engaged);

private:
	bool interlocked;
	bool firing;
};

#endif
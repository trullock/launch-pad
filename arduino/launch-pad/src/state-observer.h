#ifndef StateObserver_h
#define StateObserver_h

#include "IStateObserver.h"

class StateObserver : public IStateObserver
{
public:
	StateObserver();
	~StateObserver() {}
	virtual bool interlockEngaged();
	virtual bool firingMechanismEngaged();
};

#endif
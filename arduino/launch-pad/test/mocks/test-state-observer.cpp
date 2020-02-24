#include "test-state-observer.h"

TestStateObserver::TestStateObserver()
{
	setInterlockEngaged(false);
	setFiringMechanismEngaged(false);
}

bool TestStateObserver::interlockEngaged()
{
	return interlocked;
}

bool TestStateObserver::firingMechanismEngaged()
{
	return firing;
}

float TestStateObserver::batteryVoltage()
{
	return 12.8;
}

void TestStateObserver::setInterlockEngaged(bool engaged)
{
	interlocked = engaged;
}

void TestStateObserver::setFiringMechanismEngaged(bool engaged)
{
	firing = engaged;
}

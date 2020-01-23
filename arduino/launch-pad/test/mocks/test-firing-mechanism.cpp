#include "test-firing-mechanism.h"

void TestFiringMechanism::fire()
{
	wasFired = true;
}

void TestFiringMechanism::stopFiring()
{
}

void TestFiringMechanism::reset()
{
	wasFired = false;
}
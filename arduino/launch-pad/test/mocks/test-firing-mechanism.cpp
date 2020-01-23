#include "test-firing-mechanism.h"

TestFiringMechanism::TestFiringMechanism()
{
	reset();
}

void TestFiringMechanism::fire()
{
	wasFired = true;
}

void TestFiringMechanism::stopFiring()
{
	wasStopped = true;
}

void TestFiringMechanism::reset()
{
	wasFired = false;
	wasStopped = false;
}
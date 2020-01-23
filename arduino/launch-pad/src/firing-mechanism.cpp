#include "firing-mechanism.h"
#include <arduino.h>

#define FiringWritePin 10

FiringMechanism::FiringMechanism()
{
	pinMode(FiringWritePin, OUTPUT);
	stopFiring();
}

void FiringMechanism::fire()
{
	digitalWrite(FiringWritePin, HIGH);
}

void FiringMechanism::stopFiring()
{
	digitalWrite(FiringWritePin, LOW);
}

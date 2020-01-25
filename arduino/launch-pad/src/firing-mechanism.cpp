#include "firing-mechanism.h"
#include <arduino.h>

#define FiringWritePin 4

FiringMechanism::FiringMechanism()
{
	pinMode(FiringWritePin, OUTPUT);
	stopFiring();
}

void FiringMechanism::fire()
{
	digitalWrite(FiringWritePin, LOW);
}

void FiringMechanism::stopFiring()
{
	digitalWrite(FiringWritePin, HIGH);
}

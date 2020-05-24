#include "firing-mechanism.h"
#include <arduino.h>

// https://chewett.co.uk/blog/1066/pin-numbering-for-wemos-d1-mini-esp8266/
#define FiringWritePin 12 // D6

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

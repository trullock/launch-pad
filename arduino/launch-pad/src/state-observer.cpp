#include "state-observer.h"
#include <arduino.h>

// https://chewett.co.uk/blog/1066/pin-numbering-for-wemos-d1-mini-esp8266/
#define InterlockEngagedReadPin 5 // D1
#define FiringMechanismEngagedReadPin 4 // D2

StateObserver::StateObserver()
{
	pinMode(InterlockEngagedReadPin, INPUT);
	pinMode(FiringMechanismEngagedReadPin, INPUT);
}

bool StateObserver::interlockEngaged()
{
	int result = digitalRead(InterlockEngagedReadPin);
	return result != 0;
}

bool StateObserver::firingMechanismEngaged()
{
	int result = digitalRead(FiringMechanismEngagedReadPin);
	return result != 0;
}
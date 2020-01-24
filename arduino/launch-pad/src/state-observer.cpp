#include "state-observer.h"
#include <arduino.h>

#define InterlockEngagedReadPin 7
#define FiringMechanismEngagedReadPin 6

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
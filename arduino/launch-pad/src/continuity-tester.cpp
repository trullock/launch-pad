#include "continuity-tester.h"
#include <arduino.h>

#define ContinuityWritePin 9
#define ContinuityReadPin 8

ContinuityTester::ContinuityTester()
{
	pinMode(ContinuityWritePin, OUTPUT);
	digitalWrite(ContinuityWritePin, LOW);

	pinMode(ContinuityReadPin, INPUT);
}

bool ContinuityTester::test()
{
	digitalWrite(ContinuityWritePin, HIGH);
	// todo: delay here?
	int result = digitalRead(ContinuityReadPin);

	return result != 0;
}
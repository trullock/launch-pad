#include "continuity-tester.h"

#define ContinuityWritePin 9
#define ContinuityReadPin A0

ContinuityTester::ContinuityTester()
{
	pinMode(ContinuityWritePin, OUTPUT);
	digitalWrite(ContinuityWritePin, LOW);

	pinMode(ContinuityReadPin, INPUT_PULLUP);
}

bool ContinuityTester::test()
{
	digitalWrite(ContinuityWritePin, HIGH);
	delay(10);
	int result1 = analogRead(ContinuityReadPin);
	delay(5);
	int result2 = analogRead(ContinuityReadPin);
	delay(5);
	int result3 = analogRead(ContinuityReadPin);

	long total = result1 + result2 + result3;
	float average = total / 3;

	// circuit has a 1K-1K voltage divider, so ~500 means we have continiuty.
	// > ~500 means we're open circuit, so make it 600 for some buffer space.
	return average < 600;
}
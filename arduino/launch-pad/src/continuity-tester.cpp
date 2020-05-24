#include "continuity-tester.h"
#include <arduino.h>

// https://chewett.co.uk/blog/1066/pin-numbering-for-wemos-d1-mini-esp8266/
#define ContinuityWritePin 13 // D7
#define ContinuityReadPin 15 // D8

ContinuityTester::ContinuityTester()
{
	pinMode(ContinuityWritePin, OUTPUT);
	digitalWrite(ContinuityWritePin, LOW);

	pinMode(ContinuityReadPin, INPUT);
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

	digitalWrite(ContinuityWritePin, LOW);

	long total = result1 + result2 + result3;
	float average = total / 3;

	Serial.println(average);

	// circuit has a 1K-1K voltage divider, so ~500 means we have continiuty.
	// > ~500 means we're open circuit, so make it 600 for some buffer space.
	return average < 600;
}
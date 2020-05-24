#include "sounder.h"
#include <arduino.h>

// https://chewett.co.uk/blog/1066/pin-numbering-for-wemos-d1-mini-esp8266/
#define pinA 16 // D0
#define pinB 14 // D5
#define pinC 2 // D4

Sounder::Sounder()
{
	//pinMode(pinA, OUTPUT);
	//pinMode(pinB, OUTPUT);
	//pinMode(pinC, OUTPUT);
	silence();
}

void Sounder::silence()
{
	//digitalWrite(pinA, HIGH);
	//digitalWrite(pinB, HIGH);
	//digitalWrite(pinC, HIGH);
}

void Sounder::armed()
{
	silence();
	//digitalWrite(pinA, LOW);
}

void Sounder::passedContinuityTest()
{
	silence();
	//digitalWrite(pinB, LOW);
}

void Sounder::firing()
{
	silence();
	//digitalWrite(pinC, LOW);
}

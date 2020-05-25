#include "sounder.h"
#include <arduino.h>

// https://chewett.co.uk/blog/1066/pin-numbering-for-wemos-d1-mini-esp8266/
#define pinA 0 // D3
#define pinB 16 // D0
#define pinC 14 // D5


Sounder::Sounder()
{
	muted = false;

	pinMode(pinA, OUTPUT);
	pinMode(pinB, OUTPUT);
	pinMode(pinC, OUTPUT);

	silence();
}

void Sounder::silence()
{
	pinAMode = 1;
	pinBMode = 1;
	pinCMode = 1;

	digitalWrite(pinA, HIGH);
	digitalWrite(pinB, HIGH);
	digitalWrite(pinC, HIGH);
}

void Sounder::armed()
{
	silence();

	pinAMode = 0;
	if (!muted)
		digitalWrite(pinA, LOW);
}

void Sounder::passedContinuityTest()
{
	silence();

	pinAMode = 0;
	if (!muted)
		digitalWrite(pinA, LOW);

	pinBMode = 0;
	if (!muted)
		digitalWrite(pinB, LOW);
}

void Sounder::firing()
{
	silence();

	pinAMode = 0;
	if(!muted)
		digitalWrite(pinA, LOW);

	pinCMode = 0;
	if (!muted)
		digitalWrite(pinC, LOW);
}

void Sounder::mute()
{
	muted = true;

	digitalWrite(pinA, HIGH);
	digitalWrite(pinB, HIGH);
	digitalWrite(pinC, HIGH);
}

void Sounder::unmute()
{
	muted = false;

	digitalWrite(pinA, pinAMode == 1 ? HIGH : LOW);
	digitalWrite(pinB, pinBMode == 1 ? HIGH : LOW);
	digitalWrite(pinC, pinCMode == 1 ? HIGH : LOW);
}

#include "io.h"
#include "commands.h"
#include <arduino.h>

// https://chewett.co.uk/blog/1066/pin-numbering-for-wemos-d1-mini-esp8266/
#define ContinuityWritePin 13 // D7
#define ContinuityReadPin 15 // D8

#define ArmEngagedReadPin 2	 // D4
#define FireEngagedReadPin 3 // RX

#define ButtonEvent_None 0
#define ButtonEvent_Engaged 1
#define ButtonEvent_Disengaged 2

#define FiringWritePin 12 // D6

IO::IO()
{
	pinMode(ContinuityWritePin, OUTPUT);
	digitalWrite(ContinuityWritePin, LOW);

	pinMode(ContinuityReadPin, INPUT);

	pinMode(ArmEngagedReadPin, INPUT_PULLUP);
	// https://www.esp8266.com/wiki/doku.php?id=esp8266_gpio_pin_allocations
	pinMode(FireEngagedReadPin, FUNCTION_3);
	pinMode(FireEngagedReadPin, INPUT_PULLUP);

	pinMode(FiringWritePin, OUTPUT);
	stopFiring();
}

char IO::readManualCommand()
{
	int armEvent = this->armButtonEvent();

	if (armEvent == ButtonEvent_Engaged)
		return Command_Arm;

	if (armEvent == ButtonEvent_Disengaged)
		return Command_Disarm;

	int fireEvent = this->fireButtonEvent();

	if (fireEvent == ButtonEvent_Engaged)
		return Command_Fire;

	if (fireEvent == ButtonEvent_Disengaged)
		return Command_StopFiring;

	return Command_Null;
}

int IO::armButtonEvent()
{
	int result = digitalRead(ArmEngagedReadPin);
	bool engaged = result == 0; // pullup mode

	if (engaged != lastArmState)
	{
		// crude debounce
		delay(50);
		result = digitalRead(ArmEngagedReadPin);
		engaged = result == 0; // pullup mode
	}

	if (engaged != lastArmState)
	{
		lastArmState = engaged;
		return engaged ? ButtonEvent_Engaged : ButtonEvent_Disengaged;
	}

	return ButtonEvent_None;
}

int IO::fireButtonEvent()
{
	int result = digitalRead(FireEngagedReadPin);
	bool engaged = result == 0; // pullup mode

	if (engaged != lastFireState)
	{
		// crude debounce
		delay(50);
		result = digitalRead(FireEngagedReadPin);
		engaged = result == 0; // pullup mode
	}

	if (engaged != lastFireState)
	{
		lastFireState = engaged;
		return engaged ? ButtonEvent_Engaged : ButtonEvent_Disengaged;
	}

	return ButtonEvent_None;
}

bool IO::testContinuity()
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

void IO::fire()
{
	digitalWrite(FiringWritePin, HIGH);
}

void IO::stopFiring()
{
	digitalWrite(FiringWritePin, LOW);
}
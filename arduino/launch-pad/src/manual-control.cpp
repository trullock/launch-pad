#include "manual-control.h"
#include <arduino.h>

// https://chewett.co.uk/blog/1066/pin-numbering-for-wemos-d1-mini-esp8266/
#define ArmEngagedReadPin 2 // D4
#define FireEngagedReadPin 3 // RX

ManualControl::ManualControl()
{
	pinMode(ArmEngagedReadPin, INPUT_PULLUP);
}

bool ManualControl::arm()
{
	// don't do this in the ctor, otherwise we can never talk over serial as this uses the RX pin
	pinMode(FireEngagedReadPin, INPUT);
}

int ManualControl::armButtonEvent()
{
	int result = digitalRead(ArmEngagedReadPin);
	bool engaged = result == 0; // pullup mode

	if(engaged != lastArmState)
	{
		// crude debounce
		delay(50);
		result = digitalRead(ArmEngagedReadPin);
		engaged = result == 0; // pullup mode
	}

	if(engaged != lastArmState)
	{
		lastArmState = engaged;
		return engaged ? ButtonEvent_Engaged : ButtonEvent_Disengaged;
	}

	return ButtonEvent_None;
}

int ManualControl::fireButtonEvent()
{
	int result = digitalRead(FireEngagedReadPin);
	bool engaged = result == 1;

	if (engaged != lastFireState)
	{
		// crude debounce
		delay(50);
		result = digitalRead(ArmEngagedReadPin);
		engaged = result == 1;
	}

	if (engaged != lastFireState)
	{
		lastFireState = engaged;
		return engaged ? ButtonEvent_Engaged : ButtonEvent_Disengaged;
	}

	return ButtonEvent_None;
}
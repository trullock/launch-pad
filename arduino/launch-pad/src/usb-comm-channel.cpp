#include <Arduino.h>
#include "usb-comm-channel.h"

#define BAUD 4800

volatile bool preambleFound = 0;

UsbCommChannel::UsbCommChannel()
{
	Serial.begin(BAUD);
}

void UsbCommChannel::loop(unsigned long millis)
{
}

char UsbCommChannel::readCommand()
{
	if (!Serial.available())
		return 0;

	if (preambleFound == 0)
	{
		// check for preamble
		if (Serial.read() == ':')
		{
			preambleFound = 1;
			return this->readCommand();
		}

		return 0;
	}

	int command = Serial.read();	
	preambleFound = 0;
	return command;
}

void UsbCommChannel::write(char data)
{
	Serial.println(data);
}

bool UsbCommChannel::isConnected()
{
	// todo: implement properly
	return true;
}
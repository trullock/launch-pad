#include "../catch.h"
#include "../../src/usb-comm-channel.h"

TEST_CASE("Reading from USB comm channel") {
  

	SECTION("Prepopulated buffer") 
	{
		UsbCommChannel comms;
		Serial.reset();

		Serial.pushData(':');
		Serial.pushData('A');

		char command = comms.readCommand();

		REQUIRE(command == 'A');
	}

	SECTION("Prepopulated buffer with multiple commands")
	{
		UsbCommChannel comms;
		Serial.reset();

		Serial.pushData(':');
		Serial.pushData('A');
		Serial.pushData(':');
		Serial.pushData('B');

		char command1 = comms.readCommand();
		REQUIRE(command1 == 'A');

		char command2 = comms.readCommand();
		REQUIRE(command2 == 'B');
	}

	SECTION("Drip fed buffer")
	{
		UsbCommChannel comms;
		Serial.reset();

		Serial.pushData(':');
		comms.readCommand();
		Serial.pushData('B');
		char command = comms.readCommand();

		REQUIRE(command == 'B');
	}
}
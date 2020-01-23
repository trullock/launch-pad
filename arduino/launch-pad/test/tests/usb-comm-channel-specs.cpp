#include "../catch.h"
#include "../../usb-comm-channel.h"

TEST_CASE("Reading from USB comm channel") {
  

	SECTION("Prepopulated buffer") 
	{
		UsbCommChannel comms;
		Serial.reset();

		Serial.pushData(':');
		Serial.pushData('A');

		char command = comms.read();

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

		char command1 = comms.read();
		REQUIRE(command1 == 'A');

		char command2 = comms.read();
		REQUIRE(command2 == 'B');
	}

	SECTION("Drip fed buffer")
	{
		UsbCommChannel comms;
		Serial.reset();

		Serial.pushData(':');
		comms.read();
		Serial.pushData('B');
		char command = comms.read();

		REQUIRE(command == 'B');
	}
}
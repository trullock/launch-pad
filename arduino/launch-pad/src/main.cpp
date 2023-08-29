#include "controller.h"
#include "io.h"
#include "sounder.h"

Controller* controller;

void setup()
{
	Serial.begin(115200, SERIAL_8N1, SERIAL_TX_ONLY);

	IIO* io = new IO();
	ISounder* sounder = new Sounder();

	controller = new Controller(io, sounder);
}

void loop()
{
	unsigned long m = millis();
	controller->loop(m);
}
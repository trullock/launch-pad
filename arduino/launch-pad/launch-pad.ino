#include "src/controller.h"
#include "src/io.h"
#include "src/state-observer.h"
#include "src/sounder.h"

Controller* controller;

void setup()
{
	Serial.begin(115200, SERIAL_8N1, SERIAL_TX_ONLY);

	IIO* io = new IO();
	StateObserver* stateObserver = new StateObserver();
	ISounder* sounder = new Sounder();

	controller = new Controller(io, stateObserver, sounder);
}

void loop()
{
	unsigned long m = millis();
	controller->loop(m);
}
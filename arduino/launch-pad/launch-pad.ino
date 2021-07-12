#include "src/controller.h"
#include "src/io.h"
#include "src/state-observer.h"
#include "src/sounder.h"
#include "src/wifi-comm-channel.h"

Controller* controller;

void setup()
{
	Serial.begin(115200);

	
	ICommChannel* comms = new WifiCommChannel();
	IIO* io = new IO();
	StateObserver* stateObserver = new StateObserver();
	ISounder* sounder = new Sounder();

	controller = new Controller(comms, io, stateObserver, sounder);
}

void loop()
{
	unsigned long m = millis();
	controller->loop(m);
}
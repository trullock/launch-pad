#include "src/controller.h"
#include "src/continuity-tester.h"
#include "src/firing-mechanism.h"
#include "src/state-observer.h"
#include "src/sounder.h"
#include "src/manual-control.h"
#include "src/wifi-comm-channel.h"

Controller* controller;

void setup()
{
	Serial.begin(115200);

	
	ICommChannel* comms = new WifiCommChannel();
	IContinuityTester* continuityTester = new ContinuityTester();
	IFiringMechanism* firingMechanism = new FiringMechanism();
	StateObserver* stateObserver = new StateObserver();
	ISounder* sounder = new Sounder();
	IManualControl* manualControl = new ManualControl();

	controller = new Controller(comms, continuityTester, firingMechanism, stateObserver, sounder, manualControl);
}

void loop()
{
	unsigned long m = millis();
	controller->loop(m);
}
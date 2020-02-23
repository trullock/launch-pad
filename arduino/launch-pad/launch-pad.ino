#include "src/controller.h"
#include "src/continuity-tester.h"
#include "src/firing-mechanism.h"
#include "src/state-observer.h"
#include "src/wifi-comm-channel.h"

Controller* controller;

void setup()
{
	Serial.begin(115200);

	
	ICommChannel* comms = new WifiCommChannel();
	IContinuityTester* continuityTester = new ContinuityTester();
	IFiringMechanism* firingMechanism = new FiringMechanism();
	StateMachine* stateMachine = new StateMachine();
	StateObserver* stateObserver = new StateObserver();

	controller = new Controller(comms, stateMachine, continuityTester, firingMechanism, stateObserver);
}

void loop()
{
	unsigned long m = millis();
	controller->loop(m);
}
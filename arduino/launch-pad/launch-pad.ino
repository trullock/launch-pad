#include "src/controller.h"
#include "src/continuity-tester.h"
#include "src/firing-mechanism.h"
#include "src/usb-comm-channel.h"

Controller* controller;

void setup()
{

	ICommChannel* comms = new UsbCommChannel();
	IContinuityTester* continuityTester = new ContinuityTester();
	IFiringMechanism* firingMechanism = new FiringMechanism();
	StateMachine* stateMachine = new StateMachine();

	controller = new Controller(comms, stateMachine, continuityTester, firingMechanism);

}

void loop()
{
	unsigned long m = millis();
	controller->loop(m);
}
#ifndef Controller_h
#define Controller_h

#include "ICommChannel.h"
#include "state-machine.h"
#include "IContinuityTester.h"
#include "IFiringMechanism.h"
#include "IStateObserver.h"

#define Command_Arm 'A'
#define Command_Disarm 'D'
#define Command_TestContinuity 'C'
#define Command_Fire 'F'

#define Response_InvalidCommand 'I'
#define Response_Error 'I'
#define Response_Armed 'A'
#define Response_Disarmed 'D'
#define Response_ContinuityFailed 'N'
#define Response_ContinuityPassed 'C'
#define Response_Firing 'F'
#define Response_Timeout 'T'

#define CommandTimeoutMillis 20 * 1000

class Controller {
	public:
		Controller(ICommChannel *c, StateMachine *s, IContinuityTester* ct, IFiringMechanism* fm, IStateObserver* so);
		void loop(unsigned long millis);
	private:
		ICommChannel* comms;
		StateMachine* state;
		IContinuityTester* continuityTester;
		IFiringMechanism* firingMechanism;
		IStateObserver* stateObserver;

		void arm();
		void disarm();
		void testContinuity();
		void fire();
		void timeout();
		void handleCommand(char command);

		bool checkInterlocked();
		bool checkSaftey();
		bool haveTimedOut(char command, unsigned long millis);

		unsigned long lastCommandMillis;
};

#endif
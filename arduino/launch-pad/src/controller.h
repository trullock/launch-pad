#ifndef Controller_h
#define Controller_h

#include "commands.h"
#include "ICommChannel.h"
#include "state-machine.h"
#include "IContinuityTester.h"
#include "IFiringMechanism.h"
#include "IStateObserver.h"
#include "ISounder.h"
#include "Logger.h"

#define Response_InvalidCommand 'I'
#define Response_InvalidState 'S'
#define Response_Error 'E'
#define Response_Armed 'A'
#define Response_Disarmed 'D'
#define Response_ContinuityFailed 'N'
#define Response_ContinuityPassed 'C'
#define Response_Firing 'F'
#define Response_Timeout 'T'
#define Response_CommChannelDisconnect 'X'
#define Response_InterlockDisengaged 'L'
#define Response_FiringMechanismEngaged 'M'
#define Response_Beacon 'B'

#define CommandTimeoutMillis 20 * 1000
#define FireDurationMillis 3 * 1000

#define ReportStatusBeaconIntervalMillis 250

class Controller {
	public:
		Controller(ICommChannel *c, StateMachine *s, IContinuityTester* ct, IFiringMechanism* fm, IStateObserver* so, ISounder* sd);
		void loop(unsigned long millis);
	private:
		ICommChannel* comms;
		StateMachine* state;
		IContinuityTester* continuityTester;
		IFiringMechanism* firingMechanism;
		IStateObserver* stateObserver;
		ISounder* sounder;

		void arm(unsigned long millis);
		void disarm(char reason, unsigned long millis);
		void testContinuity(unsigned long millis);
		void fire(unsigned long millis);
		void timeout(unsigned long millis);
		void handleCommand(char command, unsigned long millis);

		void checkState(unsigned long millis);
		bool haveTimedOut(unsigned long millis);

		void reportStatusBeacon(unsigned long millis);
		void reportStatus(char response, unsigned long millis);

		unsigned long lastReportMillis;
		unsigned long lastCommandMillis;
		unsigned long firingStartedMillis;
};

#endif
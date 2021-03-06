#ifndef Controller_h
#define Controller_h

#include "commands.h"
#include "ICommChannel.h"
#include "state-machine.h"
#include "IIO.h"
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
#define Response_Muted 'Q'
#define Response_Unmuted 'W'

#define CommandTimeoutMillis 20 * 1000
#define FireDurationMillis 5 * 1000

#define ReportStatusBeaconIntervalMillis 250

class Controller {
	public:
		Controller(ICommChannel *c, IIO *io, IStateObserver *so, ISounder *sd);
		void loop(unsigned long millis);
	private:
		ICommChannel* comms;
		StateMachine* state;
		IIO* io;
		IStateObserver* stateObserver;
		ISounder* sounder;

		void arm(unsigned long millis);
		void disarm(char reason, unsigned long millis);
		void testContinuity(unsigned long millis);
		void fire(unsigned long millis);
		void timeout(unsigned long millis);
		void handleCommand(char command, unsigned long millis);

		void mute(unsigned long millis);
		void unmute(unsigned long millis);

		void checkState(unsigned long millis);
		bool haveTimedOut(unsigned long millis);

		void reportStatusBeacon(unsigned long millis);
		void reportStatus(char response, unsigned long millis);

		unsigned long lastReportMillis;
		unsigned long lastCommandMillis;
		unsigned long firingStartedMillis;
		bool underManualControl;
};

#endif

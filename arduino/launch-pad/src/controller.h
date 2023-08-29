#ifndef Controller_h
#define Controller_h

#include "commands.h"
#include "state-machine.h"
#include "IIO.h"
#include "IStateObserver.h"
#include "ISounder.h"
#include "Logger.h"

class Controller {
	public:
		Controller(IIO *io, IStateObserver *so, ISounder *sd);
		void loop(unsigned long millis);
	private:
		StateMachine* state;
		IIO* io;
		IStateObserver* stateObserver;
		ISounder* sounder;

		void arm(unsigned long millis);
		void disarm(unsigned long millis);
		void testContinuity(unsigned long millis);
		void fire(unsigned long millis);
		void timeout(unsigned long millis);
		void handleCommand(char command, unsigned long millis);

		void checkState(unsigned long millis);

		unsigned long lastCommandMillis;
		unsigned long firingStartedMillis;
};

#endif

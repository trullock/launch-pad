#ifndef Controller_h
#define Controller_h

#include "commands.h"
#include "IIO.h"
#include "ISounder.h"
#include "Logger.h"

class Controller {
	public:
		Controller(IIO *io, ISounder *sd);
		void loop(unsigned long millis);
	private:
		IIO* io;

		bool armed = false;
		bool firing = false;

		ISounder* sounder;

		void arm(unsigned long millis);
		void disarm(unsigned long millis);
		void testContinuity(unsigned long millis);
		void fire(unsigned long millis);
		void stopFiring(unsigned long millis);
		void handleCommand(char command, unsigned long millis);

		unsigned long lastCommandMillis = 0;
		unsigned long firingStartedMillis = 0;
};

#endif

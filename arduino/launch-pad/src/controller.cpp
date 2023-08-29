#include "controller.h"
#include "status.h"
#include "states.h"

#define RelayActuationMillis 50

Controller::Controller(IIO *io, ISounder *sd)
{
	this->io = io;
	this->sounder = sd;

	this->lastCommandMillis = 0;
	this->firingStartedMillis = 0;
}

void Controller::loop(unsigned long millis)
{
	if(this->armed)
		testContinuity(millis);

	char command = this->io->readManualCommand();

	if (command == Command_Null)
		return;

	Log.print("Controller::loop: Handling command: ");
	Log.println(command);

	handleCommand(command, millis);
}


void Controller::handleCommand(char command, unsigned long millis)
{
	lastCommandMillis = millis;

	switch (command)
	{
		case Command_Arm:
			arm(millis);
			break;

		case Command_Disarm:
			disarm(millis);
			break;

		case Command_TestContinuity:
			testContinuity(millis);
			break;

		case Command_Fire:
			fire(millis);
			break;

		case Command_StopFiring:
			stopFiring(millis);
			break;
	}
}

void Controller::arm(unsigned long millis)
{
	Log.println("Controller::arm: Attempting to Arm");

	this->armed = true;
	this->firing = false;
	sounder->armed();
	Log.println("Controller::arm: Arming successful");
}

void Controller::disarm(unsigned long millis)
{
	Log.println("Controller::disarm: Attempting to Disarm");

	io->stopFiring();
	firingStartedMillis = 0;
	sounder->silence();

	this->armed = false;
	this->firing = false;

	Log.println("Controller::disarm: Disarm successful");
}

void Controller::testContinuity(unsigned long millis)
{
	// dont bother whilst firing
	if(this->firing)
		return;

	//Log.println("Controller::testContinuity: Attempting to Test Continuity");

	if(!this->armed)
	{
		Log.println("Controller::testContinuity: Testing unsuccessful, not armed");
		return;
	}

	if (io->testContinuity())
	{
		//Log.println("Controller::testContinuity: Continuity=true");

		sounder->passedContinuityTest();
		//Log.println("Controller::testContinuity: Continuity Test successful");
		return;
	}

	sounder->armed();
	//Log.println("Controller::testContinuity: Continuity Test failed");
}

void Controller::fire(unsigned long millis)
{
	Log.println("Controller::fire: Attempting to Fire");

	if(!this->armed)
	{
		Log.println("Controller::fire: Firing initiation unsuccessful, not a valid command in this state");
		disarm(millis);
		return;
	}

	this->firing = true;
	this->sounder->firing();
	this->firingStartedMillis = millis;
	this->io->fire();

	Log.println("Controller::fire: Firing initiation successful");
}

void Controller::stopFiring(unsigned long millis)
{
	Log.println("Controller::stopFiring: Attempting to Stop Fire");

	if(!armed)
	{
		Log.println("Controller::stopFiring: Can't stop firing, not armed");
		return;
	}

	this->firing = false;
	this->sounder->armed();
	this->firingStartedMillis = 0;
	this->io->stopFiring();

	Log.println("Controller::stopFiring: Stop-Firing initiation successful");
}
#include "controller.h"
#include "status.h"

#define RelayActuationMillis 50

Controller::Controller(IIO *io, IStateObserver *so, ISounder *sd)
{
	this->state = new StateMachine();
	this->io = io;
	this->stateObserver = so;
	this->sounder = sd;

	this->lastCommandMillis = 0;
	this->firingStartedMillis = 0;
}

void Controller::loop(unsigned long millis)
{
	checkState(millis);

	char command = this->io->readManualCommand();

	if (command == Command_Null)
		return;

	Log.print("Controller::loop: Handling command: ");
	Log.println(command);

	handleCommand(command, millis);

	// this hack stinks
	if(command == Command_Arm)
		handleCommand(Command_TestContinuity, millis);
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
	}
}

void Controller::checkState(unsigned long millis)
{
	char currentState = state->getState();

	// check interlock status
	switch (currentState)
	{
		case State_Armed:
		case State_ContinuityPassed:
		case State_Firing:
			if (!stateObserver->interlockEngaged())
			{
				Log.println("Controller::checkState: Interlock disengaged in required state, disarming");
				disarm(millis);
			}
	}

	// check continuity status
	switch (currentState)
	{
		case State_ContinuityPassed:
		// removed due to some ignitors not firing before continuity breaks
		//case State_Firing:
			if (!io->testContinuity())
			{
				Log.println("Controller::checkState: Continutity broken, disarming");
				disarm(millis);
			}
	}

	// check firing status
	if (currentState != State_Firing && stateObserver->firingMechanismEngaged())
	{
		Log.println("Controller::checkState: Firing mechanism enabled in unexpected state, disarming");
		disarm(millis);
	}
}

void Controller::arm(unsigned long millis)
{
	Log.println("Controller::arm: Attempting to Arm");

	if (!stateObserver->interlockEngaged())
	{
		Log.println("Controller::arm: Cannot arm, interlock not engaged. Disarming");
		disarm(millis);
		return;
	}

	if(state->arm())
	{
		sounder->armed();
		Log.println("Controller::arm: Arming successful");
	}
	else
	{
		Log.println("Controller::arm: Arming unsuccessful, not a valid command in this state");
	}
}

void Controller::disarm(unsigned long millis)
{
	Log.println("Controller::disarm: Attempting to Disarm");

	io->stopFiring();
	firingStartedMillis = 0;
	sounder->silence();

	if(state->disarm())
		Log.println("Controller::disarm: Disarm successful");
	else
		Log.println("Controller::disarm: Disarm unsuccessful, not a valid command in this state");
}

void Controller::testContinuity(unsigned long millis)
{
	Log.println("Controller::testContinuity: Attempting to Test Continuity");

	if(!state->canTestContinuity())
	{
		disarm(millis);
		Log.println("Controller::testContinuity: Testing unsuccessful, not a valid command in this state");
		return;
	}

	if (io->testContinuity())
	{
		Log.println("Controller::testContinuity: Continuity=true");

		if(state->passContinuity())
		{
			sounder->passedContinuityTest();
			Log.println("Controller::testContinuity: Continuity Test successful");
			return;
		}

		Log.println("Controller::testContinuity: State machine change to ContinuityPassed unsuccessful, disarming");
		disarm(millis);
		return;
	}

	disarm(millis);
	Log.println("Controller::testContinuity: Continuity Test failed, disarming");
}

void Controller::fire(unsigned long millis)
{
	Log.println("Controller::fire: Attempting to Fire");

	if(!state->fire())
	{
		Log.println("Controller::fire: Firing initiation unsuccessful, not a valid command in this state");
		disarm(millis);
		return;
	}

	this->sounder->firing();
	this->firingStartedMillis = millis;
	this->io->fire();

	Log.println("Controller::fire: Firing initiation successful");
}
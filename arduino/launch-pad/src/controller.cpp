#include "controller.h"


Controller::Controller(ICommChannel* c, StateMachine* s, IContinuityTester* ct, IFiringMechanism* fm, IStateObserver* so)
{
	comms = c;
	state = s;
	continuityTester = ct;
	firingMechanism = fm;
	stateObserver = so;

	lastCommandMillis = 0;
	firingStartedMillis = 0;
}

void Controller::loop(unsigned long millis)
{
	comms->loop(millis);

	if(!comms->isConnected() && state->getState() != State_Ready)
	{
		Log.println("Controller::loop: Comms channel disconnected, disarming");
		disarm();
		return;
	}
	
	checkState(millis);

	if (haveTimedOut(millis))
	{
		Log.println("Controller::loop: Command timeout elapsed, disarming");
		timeout();
		return;
	}

	char command = comms->read();
	if(command == 0)
		return;

	Log.print("Controller::loop: Handling command: ");
	Log.println(command);

	handleCommand(command, millis);
}

bool Controller::haveTimedOut(unsigned long millis)
{
	char currentState = state->getState();
	switch (currentState)
	{
		case State_Armed:
		case State_ContinuityPassed:
		case State_Firing:
			if (millis - lastCommandMillis >= CommandTimeoutMillis)
				return true;
	}

	return false;
}

void Controller::handleCommand(char command, unsigned long millis)
{
	lastCommandMillis = millis;

	switch (command)
	{
		case Command_Arm:
			arm();
			break;

		case Command_Disarm:
			disarm();
			break;

		case Command_TestContinuity:
			testContinuity();
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
				disarm();
				comms->write(Response_InvalidState);
			}
	}

	// check continuity status
	switch (currentState)
	{
		case State_ContinuityPassed:
		case State_Firing:
			if (!continuityTester->test())
			{
				Log.println("Controller::checkState: Continutity broken, disarming");
				disarm();
				comms->write(Response_InvalidState);
			}
	}

	// check firing status
	if (currentState != State_Firing && stateObserver->firingMechanismEngaged())
	{
		Log.println("Controller::checkState: Firing mechanism enabled in unexpected state, disarming");
		disarm();
		comms->write(Response_InvalidState);
	}

	// check firing duration
	if(currentState == State_Firing && firingStartedMillis + FireDurationMillis <= millis)
	{
		Log.println("Controller::checkState: Firing duration elapsed, disarming");
		disarm();
	
	}
}

void Controller::arm()
{
	Log.println("Controller::arm: Attempting to Arm");

	if (!stateObserver->interlockEngaged())
	{
		Log.println("Controller::arm: Cannot arm, interlock not engaged. Disarming");
		disarm();
		comms->write(Response_InvalidState);
		// interlock not engaged
		return;
	}

	if(state->arm())
	{
		Log.println("Controller::arm: Arming successful");
		comms->write(Response_Armed);
	}
	else
	{
		Log.println("Controller::arm: Arming unsuccessful, not a valid command in this state");
		comms->write(Response_InvalidCommand);
	}
}

void Controller::disarm()
{
	Log.println("Controller::disarm: Attempting to Disarm");

	firingMechanism->stopFiring();

	if(state->disarm())
	{
		Log.println("Controller::disarm: Disarm successful");
		comms->write(Response_Disarmed);
	}
	else
	{
		Log.println("Controller::disarm: Disarm unsuccessful, not a valid command in this state");
		comms->write(Response_InvalidCommand);
	}
}

void Controller::timeout()
{
	disarm();
	comms->write(Response_Timeout);
}

void Controller::testContinuity()
{
	Log.println("Controller::testContinuity: Attempting to Test Continuity");

	if(!state->canTestContinuity())
	{
		disarm();
		Log.println("Controller::testContinuity: Testing unsuccessful, not a valid command in this state");
		comms->write(Response_InvalidCommand);
		return;
	}

	if (continuityTester->test())
	{
		Log.println("Controller::testContinuity: Continuity=true");

		if(state->passContinuity())
		{
			Log.println("Controller::testContinuity: Continuity Test successful");
			comms->write(Response_ContinuityPassed);
			return;
		}

		Log.println("Controller::testContinuity: Continuity Test unsuccessful, not a valid command in this state");
		disarm();
		comms->write(Response_Error);
		return;
	}

	disarm();
	Log.println("Controller::testContinuity: Continuity Test failed, disarming");
	comms->write(Response_ContinuityFailed);
}

void Controller::fire(unsigned long millis)
{
	Log.println("Controller::fire: Attempting to Fire");

	if(!state->fire())
	{
		Log.println("Controller::fire: Firing initiation unsuccessful, not a valid command in this state");
		disarm();
		comms->write(Response_InvalidCommand);
		return;
	}

	firingStartedMillis = millis;
	firingMechanism->fire();
	Log.println("Controller::fire: Firing initiation successful");
	comms->write(Response_Firing);
}
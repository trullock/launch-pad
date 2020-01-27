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
	checkState(millis);

	if (haveTimedOut(millis))
	{
		timeout();
		return;
	}

	char command = comms->read();
	if(command == 0)
		return;
	
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
			disarm();
			comms->write(Response_InvalidState);
			// interlock not engaged
		}
	}

	// check interlock status
	switch (currentState)
	{
	case State_ContinuityPassed:
	case State_Firing:
		if (!continuityTester->test())
		{
			disarm();
			comms->write(Response_InvalidState);
			// interlock not engaged
		}
	}

	if (currentState != State_Firing && stateObserver->firingMechanismEngaged())
	{
		disarm();
		comms->write(Response_InvalidState);
		// firing when we shouldnt be
	}

	if(currentState == State_Firing)
	{
		if(firingStartedMillis + FireDurationMillis <= millis)
		{
			disarm();
			// finished firing
		}
	}
}

void Controller::arm()
{
	if (!stateObserver->interlockEngaged())
	{
		disarm();
		comms->write(Response_InvalidState);
		// interlock not engaged
		return;
	}

	if(state->arm())
		comms->write(Response_Armed);
	else
		comms->write(Response_InvalidCommand);
}

void Controller::disarm()
{
	firingMechanism->stopFiring();

	if(state->disarm())
		comms->write(Response_Disarmed);
	else
		comms->write(Response_InvalidCommand);
}

void Controller::timeout()
{
	disarm();
	comms->write(Response_Timeout);
}

void Controller::testContinuity()
{
	if(!state->canTestContinuity())
	{
		disarm();
		comms->write(Response_InvalidCommand);
		return;
	}

	if (continuityTester->test())
	{
		if(state->passContinuity())
		{
			comms->write(Response_ContinuityPassed);
			return;
		}

		disarm();
		comms->write(Response_Error);
		return;
	}

	disarm();
	comms->write(Response_ContinuityFailed);
}

void Controller::fire(unsigned long millis)
{
	if(!state->fire())
	{
		disarm();
		comms->write(Response_InvalidCommand);
		return;
	}

	firingStartedMillis = millis;
	firingMechanism->fire();
	comms->write(Response_Firing);
}
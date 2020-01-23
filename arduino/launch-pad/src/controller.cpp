#include "controller.h"


Controller::Controller(ICommChannel* c, StateMachine* s, IContinuityTester* ct, IFiringMechanism* fm)
{
	comms = c;
	state = s;
	continuityTester = ct;
	firingMechanism = fm;
	lastCommandMillis = 0;
}

void Controller::loop(unsigned long millis)
{
	char command = comms->read();
	if(command == 0)
		return;
	
	if(haveTimedOut(command, millis)){
		timeout();
		return;
	}

	lastCommandMillis = millis;
	handleCommand(command);
}

bool Controller::haveTimedOut(char command, unsigned long millis)
{
	switch (command)
	{
		case Command_TestContinuity:
		case Command_Fire:
			if (millis - lastCommandMillis >= CommandTimeoutMillis)
				return true;
	}

	return false;
}

void Controller::handleCommand(char command)
{
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
			fire();
			break;
	}
}

void Controller::arm()
{
	if(state->arm())
		comms->write(Response_Armed);
	else
		comms->write(Response_InvalidCommand);
}

void Controller::disarm()
{
	if(state->disarm())
		comms->write(Response_Disarmed);
	else
		comms->write(Response_InvalidCommand);
}

void Controller::timeout()
{
	comms->write(Response_Timeout);
	disarm();
}

void Controller::testContinuity()
{
	if(!state->canTestContinuity())
	{
		state->disarm();
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

		state->disarm();
		comms->write(Response_Error);
		return;
	}

	state->disarm();
	comms->write(Response_ContinuityFailed);
}

void Controller::fire()
{
	if(!state->fire())
	{
		state->disarm();
		comms->write(Response_InvalidCommand);
		return;
	}

	firingMechanism->fire();
	comms->write(Response_Firing);
}
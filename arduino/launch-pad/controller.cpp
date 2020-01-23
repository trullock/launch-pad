#include "controller.h"

Controller::Controller(ICommChannel* c, StateMachine* s, IContinuityTester* ct, IFiringMechanism* fm)
{
	comms = c;
	state = s;
	continuityTester = ct;
	firingMechanism = fm;
}

void Controller::loop(unsigned long millis)
{
	char command = comms->read(); // then read in command
	switch (command)
	{
		case 0:
			break;

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
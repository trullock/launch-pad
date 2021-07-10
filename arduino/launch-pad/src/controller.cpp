#include "controller.h"
#include "status.h"

#define RelayActuationMillis 50

Controller::Controller(ICommChannel *c, IContinuityTester *ct, IFiringMechanism *fm, IStateObserver *so, ISounder *sd, IManualControl* mc)
{
	comms = c;
	state = new StateMachine();
	continuityTester = ct;
	firingMechanism = fm;
	stateObserver = so;
	sounder = sd;
	manualControl = mc;

	lastCommandMillis = 0;
	firingStartedMillis = 0;
}

void Controller::loop(unsigned long millis)
{
	comms->loop(millis);

	if(underManualControl)
	{
		checkState(millis);
		checkManualControl(millis);
	}
	else
	{
		if (!comms->isConnected() && state->getState() != State_Disarmed)
		{
			Log.println("Controller::loop: Comms channel disconnected, disarming");
			disarm(Response_CommChannelDisconnect, millis);
			return;
		}

		checkState(millis);

		if (haveTimedOut(millis))
		{
			Log.println("Controller::loop: Command timeout elapsed, disarming");
			timeout(millis);
			return;
		}

		char command = comms->readCommand();
		if (command == Command_Null)
		{
			reportStatusBeacon(millis);
			return;
		}

		Log.print("Controller::loop: Handling command: ");
		Log.println(command);

		handleCommand(command, millis);
	}
		
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

void Controller::reportStatusBeacon(unsigned long millis) 
{
	if (lastReportMillis + ReportStatusBeaconIntervalMillis > millis)
		return;

	reportStatus(Response_Beacon, millis);
}

void Controller::reportStatus(char response, unsigned long millis)
{
	lastReportMillis = millis;
	
	Status st;
	st.interlockEngaged = stateObserver->interlockEngaged();
	st.firingMechanismEngaged = stateObserver->firingMechanismEngaged();
	st.batteryVoltage = stateObserver->batteryVoltage();
	st.state = state->getState();

	comms->writeStatus(response, st);
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
			disarm(Response_Disarmed, millis);
			break;

		case Command_TestContinuity:
			testContinuity(millis);
			break;

		case Command_Fire:
			fire(millis);
			break;

		case Command_Silence:
			mute(millis);
			break;

		case Command_Loud:
			unmute(millis);
			break;

		default:
			reportStatusBeacon(millis);
			break;
	}
}

void Controller::checkManualControl(unsigned long millis)
{
	char currentState = state->getState();
	bool armButtonEvent = this->manualControl->armButtonEvent();
	if (armButtonEvent == ButtonEvent_Engaged)
	{
		underManualControl = true;
		
		if(currentState == State_Disarmed)
		{
			arm(millis);
			testContinuity(millis);
		}
		return;
	}

	if (armButtonEvent == ButtonEvent_Disengaged)
	{
		disarm(Response_Disarmed, millis);
		return;
	}

	bool fireButtonEvent = this->manualControl->fireButtonEvent();
	if (fireButtonEvent == ButtonEvent_Engaged)
	{
		if(currentState == State_ContinuityPassed)
		{
			fire(millis);
		}
		return;
	}

	if(fireButtonEvent == ButtonEvent_Disengaged)
	{
		disarm(Response_Disarmed, millis);
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
				disarm(Response_InterlockDisengaged, millis);
			}
	}

	// check continuity status
	switch (currentState)
	{
		case State_ContinuityPassed:
		// removed due to some ignitors not firing before continuity breaks
		//case State_Firing:
			if (!continuityTester->test())
			{
				Log.println("Controller::checkState: Continutity broken, disarming");
				disarm(Response_ContinuityFailed, millis);
			}
	}

	// check firing status
	if (currentState != State_Firing && stateObserver->firingMechanismEngaged())
	{
		Log.println("Controller::checkState: Firing mechanism enabled in unexpected state, disarming");
		disarm(Response_FiringMechanismEngaged, millis);
	}

	// check firing duration
	if(!underManualControl && currentState == State_Firing && firingStartedMillis + FireDurationMillis <= millis)
	{
		Log.println("Controller::checkState: Firing duration elapsed, disarming");
		disarm(Response_Disarmed, millis);
	}
}

void Controller::arm(unsigned long millis)
{
	Log.println("Controller::arm: Attempting to Arm");

	if (!stateObserver->interlockEngaged())
	{
		Log.println("Controller::arm: Cannot arm, interlock not engaged. Disarming");
		disarm(Response_InterlockDisengaged, millis);
		return;
	}

	if(state->arm())
	{
		sounder->armed();
		manualControl->arm();
		Log.println("Controller::arm: Arming successful");
		reportStatus(Response_Armed, millis);
	}
	else
	{
		Log.println("Controller::arm: Arming unsuccessful, not a valid command in this state");
		reportStatus(Response_InvalidCommand, millis);
	}
}

void Controller::disarm(char reason, unsigned long millis)
{
	Log.println("Controller::disarm: Attempting to Disarm");

	firingMechanism->stopFiring();
	firingStartedMillis = 0;
	sounder->silence();

	if(state->disarm())
	{
		// give the relay time to move
		delay(RelayActuationMillis);

		Log.println("Controller::disarm: Disarm successful");
		reportStatus(reason, millis);
	}
	else
	{
		Log.println("Controller::disarm: Disarm unsuccessful, not a valid command in this state");
		reportStatus(Response_InvalidCommand, millis);
	}
}

void Controller::timeout(unsigned long millis)
{
	disarm(Response_Timeout, millis);
}

void Controller::testContinuity(unsigned long millis)
{
	Log.println("Controller::testContinuity: Attempting to Test Continuity");

	if(!state->canTestContinuity())
	{
		disarm(Response_InvalidCommand, millis);
		Log.println("Controller::testContinuity: Testing unsuccessful, not a valid command in this state");
		return;
	}

	if (continuityTester->test())
	{
		Log.println("Controller::testContinuity: Continuity=true");

		if(state->passContinuity())
		{
			sounder->passedContinuityTest();
			reportStatus(Response_ContinuityPassed, millis);
			Log.println("Controller::testContinuity: Continuity Test successful");
			return;
		}

		Log.println("Controller::testContinuity: State machine change to ContinuityPassed unsuccessful, disarming");
		disarm(Response_Error, millis);
		return;
	}

	disarm(Response_ContinuityFailed, millis);
	Log.println("Controller::testContinuity: Continuity Test failed, disarming");
}

void Controller::fire(unsigned long millis)
{
	Log.println("Controller::fire: Attempting to Fire");

	if(!state->fire())
	{
		Log.println("Controller::fire: Firing initiation unsuccessful, not a valid command in this state");
		disarm(Response_InvalidCommand, millis);
		return;
	}

	sounder->firing();
	firingStartedMillis = millis;
	firingMechanism->fire();

	// give the relay time to move
	delay(RelayActuationMillis);

	Log.println("Controller::fire: Firing initiation successful");
	reportStatus(Response_Firing, millis);
}

void Controller::mute(unsigned long millis)
{
	Log.println("Controller::mute: Muting");

	sounder->mute();

	Log.println("Controller::mute: Muted");
	reportStatus(Response_Muted, millis);
}

void Controller::unmute(unsigned long millis)
{
	Log.println("Controller::unmute: Louding");

	sounder->unmute();

	Log.println("Controller::unmute: Louded");
	reportStatus(Response_Unmuted, millis);
}
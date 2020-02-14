#include "state-machine.h"

StateMachine::StateMachine()
{
	state = State_Disarmed;
}

bool StateMachine::arm(){
	if (state == State_Disarmed)
	{
		state = State_Armed;
		return true;
	}

	return false;
}

bool StateMachine::disarm()
{
	state = State_Disarmed;
	return true;
}

char StateMachine::getState()
{
	return state;
}

bool StateMachine::canTestContinuity()
{
	if(state == State_Armed || state == State_ContinuityPassed)
		return true;

	return false;
}

bool StateMachine::passContinuity()
{
	if(state == State_Armed){
		state = State_ContinuityPassed;
		return true;
	}

	return false;
}

bool StateMachine::fire() {
	if(state == State_ContinuityPassed){
		state = State_Firing;
		return true;
	}

	return false;
}
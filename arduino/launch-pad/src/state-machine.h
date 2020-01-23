#ifndef StateMachine_h
#define StateMachine_h


#define State_Ready 'R'
#define State_Armed 'A'
#define State_ContinuityPassed 'C'
#define State_Firing 'F'

class StateMachine
{
public:
	StateMachine();
	bool arm();
	bool disarm();
	bool canTestContinuity();
	bool passContinuity();
	bool fire();
	char getState();

private:
	char state;
};

#endif
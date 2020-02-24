#ifndef Status_h
#define Status_h

struct Status
{
	bool interlockEngaged;
	bool firingMechanismEngaged;
	float batteryVoltage;
	char state;
};

#endif
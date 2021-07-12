#ifndef ManualControl_h
#define ManualControl_h

#include "IManualControl.h"


class ManualControl : public IManualControl
{
	bool lastArmState = false;
	bool lastFireState = false;

	virtual int armButtonEvent();
	virtual int fireButtonEvent();

public:
	ManualControl();
	~ManualControl() {}

	virtual char readCommand();
};

#endif
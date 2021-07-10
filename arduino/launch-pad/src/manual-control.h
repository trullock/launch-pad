#ifndef ManualControl_h
#define ManualControl_h

#include "IManualControl.h"


class ManualControl : public IManualControl
{
public:
	ManualControl();
	~ManualControl() {}
	virtual bool arm();
	virtual int armButtonEvent();
	virtual int fireButtonEvent();

	bool lastArmState = false;
	bool lastFireState = false;
};

#endif
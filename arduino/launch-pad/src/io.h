#ifndef IO_h
#define IO_h

#include "IIO.h"

class IO : public IIO
{
	bool lastArmState = false;
	bool lastFireState = false;

	virtual int armButtonEvent();
	virtual int fireButtonEvent();

public:
	IO();
	~IO() {}
	virtual bool testContinuity();
	
	virtual char readManualCommand();

	virtual void fire();
	virtual void stopFiring();
};

#endif
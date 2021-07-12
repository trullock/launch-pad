#ifndef IIO_h
#define IIO_h

class IIO
{
public:
	virtual ~IIO() {}
	
	virtual bool testContinuity() = 0;
	
	virtual char readManualCommand() = 0;

	virtual void fire() = 0;
	virtual void stopFiring() = 0;
};

#endif
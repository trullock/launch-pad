#ifndef IFiringMechanism_h
#define IFiringMechanism_h

class IFiringMechanism
{
public:
	virtual ~IFiringMechanism(){};
	virtual void fire() = 0;
	virtual void stopFiring() = 0;
};

#endif
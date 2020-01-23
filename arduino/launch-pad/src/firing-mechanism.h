#ifndef FiringMechanism_h
#define FiringMechanism_h

class FiringMechanism
{
public:
	FiringMechanism();
	~FiringMechanism(){};
	virtual void fire();
	virtual void stopFiring();
};

#endif
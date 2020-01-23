#ifndef IContinuityTester_h
#define IContinuityTester_h

class IContinuityTester
{
public:
	virtual ~IContinuityTester() {}
	virtual bool test() = 0;
};

#endif
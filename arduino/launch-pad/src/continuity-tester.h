#ifndef ContinuityTester_h
#define ContinuityTester_h

#include "IContinuityTester.h"

class ContinuityTester : public IContinuityTester
{
public:
	ContinuityTester();
	~ContinuityTester() {}
	virtual bool test();
};

#endif
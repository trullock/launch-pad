#include "../../continuity-tester.h"

class TestContinuityTester : public IContinuityTester
{
public:
	TestContinuityTester();
	~TestContinuityTester() {}
	virtual bool test();
	void setResult(bool r);
	void reset();
	bool wasTested;
private:
	bool result;
};
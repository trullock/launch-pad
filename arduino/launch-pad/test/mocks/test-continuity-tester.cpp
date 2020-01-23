#include "test-continuity-tester.h"

TestContinuityTester::TestContinuityTester()
{
	wasTested = false;
}

bool TestContinuityTester::test()
{
	wasTested = true;
	return result;
}

void TestContinuityTester::setResult(bool r)
{
	result = r;
}

void TestContinuityTester::reset()
{
	wasTested = false;
}
#include "../catch.h"
#include "../../src/state-machine.h"

TEST_CASE("State Machine") {

	SECTION("Ready to Armed")
	{
		StateMachine m;
		REQUIRE(m.arm() == true);
	}

	SECTION("Ready can't TestContinuity")
	{
		StateMachine m;
		REQUIRE(m.canTestContinuity() == false);
	}

	SECTION("Ready to Continuity Pass")
	{
		StateMachine m;
		REQUIRE(m.passContinuity() == false);
	}

	SECTION("Ready to Firing")
	{
		StateMachine m;
		REQUIRE(m.fire() == false);
	}

	SECTION("Armed to Disarmed/ready")
	{
		StateMachine m;
		REQUIRE(m.arm() == true);
		REQUIRE(m.disarm() == true);
	}

	SECTION("Armed can TestContinuity")
	{
		StateMachine m;
		REQUIRE(m.arm() == true);
		REQUIRE(m.canTestContinuity() == true);
	}

	SECTION("Armed to Continuity Pass")
	{
		StateMachine m;
		REQUIRE(m.arm() == true);
		REQUIRE(m.passContinuity() == true);
	}

	SECTION("Armed to Firing")
	{
		StateMachine m;
		REQUIRE(m.arm() == true);
		REQUIRE(m.fire() == false);
	}

	SECTION("ContinuityPassed to Disarmed/ready")
	{
		StateMachine m;
		REQUIRE(m.arm() == true);
		REQUIRE(m.passContinuity() == true);
		REQUIRE(m.disarm() == true);
	}

	SECTION("ContinuityPassed can TestContinuity")
	{
		StateMachine m;
		REQUIRE(m.arm() == true);
		REQUIRE(m.passContinuity() == true);
		REQUIRE(m.canTestContinuity() == true);
	}

	SECTION("ContinuityPassed to Firing")
	{
		StateMachine m;
		REQUIRE(m.arm() == true);
		REQUIRE(m.passContinuity() == true);
		REQUIRE(m.fire() == true);
	}

	SECTION("Firing can't TestContinuity")
	{
		StateMachine m;
		REQUIRE(m.arm() == true);
		REQUIRE(m.passContinuity() == true);
		REQUIRE(m.fire() == true);
		REQUIRE(m.canTestContinuity() == false);
	}

	SECTION("Multiple state navigations to fire")
	{
		StateMachine m;
		REQUIRE(m.arm() == true);
		REQUIRE(m.disarm() == true);
		REQUIRE(m.arm() == true);
		REQUIRE(m.passContinuity() == true);
		REQUIRE(m.disarm() == true);
		REQUIRE(m.arm() == true);
		REQUIRE(m.passContinuity() == true);
		REQUIRE(m.fire() == true);
	}
}
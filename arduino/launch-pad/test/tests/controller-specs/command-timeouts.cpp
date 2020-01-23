#include "../../catch.h"
#include "../../mocks/test-comm-channel.h"
#include "../../mocks/test-continuity-tester.h"
#include "../../mocks/test-firing-mechanism.h"
#include "../../../src/controller.h"

TEST_CASE("Command Timeouts") {

	TestCommChannel comms;
	TestContinuityTester continuityTester;
	StateMachine state;
	TestFiringMechanism firingMechanism;

	Controller controller(&comms, &state, &continuityTester, &firingMechanism);

	//reset
	comms.reset();
	state.disarm();
	firingMechanism.reset();

	SECTION("Timeout between arm and continuity test should fail, system should be disarmed")
	{
		comms.pushReadChar(Command_Arm);
		controller.loop(0);

		comms.pushReadChar(Command_TestContinuity);
		controller.loop(CommandTimeoutMillis);

		REQUIRE(comms.getLastChar() == Response_Disarmed);

		REQUIRE(state.getState() == State_Ready);

		// flush
		for (int i = 0; i < 100; i++)
			controller.loop(CommandTimeoutMillis + i);

		REQUIRE(firingMechanism.wasFired == false);
	}

	SECTION("Timeout between continuity-pass and fire should fail, system should be disarmed")
	{
		comms.pushReadChar(Command_Arm);
		controller.loop(0);

		// make continuity pass
		continuityTester.setResult(true);

		comms.pushReadChar(Command_TestContinuity);
		controller.loop(10);

		comms.pushReadChar(Command_Fire);
		controller.loop(10 + CommandTimeoutMillis);

		REQUIRE(comms.getLastChar() == Response_Disarmed);
		REQUIRE(state.getState() == State_Ready);

		// flush
		for (int i = 0; i < 100; i++)
			controller.loop(10 + CommandTimeoutMillis + i);

		REQUIRE(firingMechanism.wasFired == false);
	}
}
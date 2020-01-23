#include "../../catch.h"
#include "../../mocks/test-comm-channel.h"
#include "../../mocks/test-continuity-tester.h"
#include "../../mocks/test-firing-mechanism.h"
#include "../../mocks/test-state-observer.h"
#include "../../../src/controller.h"

TEST_CASE("Command Timeouts") {

	TestCommChannel comms;
	TestContinuityTester continuityTester;
	StateMachine state;
	TestFiringMechanism firingMechanism;
	TestStateObserver stateObserver;

	Controller controller(&comms, &state, &continuityTester, &firingMechanism, &stateObserver);

	//reset
	comms.reset();
	state.disarm();
	firingMechanism.reset();
	stateObserver.setInterlockEngaged(true);

	SECTION("Timeout between arm and continuity test should fail, system should be disarmed")
	{
		comms.pushReadChar(Command_Arm);
		controller.loop(0);

		REQUIRE(comms.getWrittenChar() == Response_Armed);

		comms.pushReadChar(Command_TestContinuity);
		controller.loop(CommandTimeoutMillis);

		REQUIRE(comms.getWrittenChar() == Response_Disarmed);
		REQUIRE(comms.getWrittenChar() == Response_Timeout);

		REQUIRE(state.getState() == State_Ready);

		// flush
		for (int i = 0; i < 16; i++)
			controller.loop(CommandTimeoutMillis + i);

		REQUIRE(firingMechanism.wasFired == false);
	}

	SECTION("Timeout between continuity-pass and fire should fail, system should be disarmed")
	{
		comms.pushReadChar(Command_Arm);
		controller.loop(0);

		REQUIRE(comms.getWrittenChar() == Response_Armed);

		// make continuity pass
		continuityTester.setResult(true);

		comms.pushReadChar(Command_TestContinuity);
		controller.loop(10);

		REQUIRE(comms.getWrittenChar() == Response_ContinuityPassed);

		comms.pushReadChar(Command_Fire);
		controller.loop(10 + CommandTimeoutMillis);

		REQUIRE(comms.getWrittenChar() == Response_Disarmed);
		REQUIRE(comms.getWrittenChar() == Response_Timeout);
		REQUIRE(state.getState() == State_Ready);

		// flush
		for (int i = 0; i < 16; i++)
			controller.loop(10 + CommandTimeoutMillis + i);

		REQUIRE(firingMechanism.wasFired == false);
	}
}
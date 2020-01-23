#include "../../catch.h"
#include "../../mocks/test-comm-channel.h"
#include "../../mocks/test-continuity-tester.h"
#include "../../mocks/test-firing-mechanism.h"
#include "../../../src/controller.h"

TEST_CASE("Test Continuity") {

	TestCommChannel comms;
	TestContinuityTester continuityTester;
	StateMachine state;
	TestFiringMechanism firingMechanism;

	Controller controller(&comms, &state, &continuityTester, &firingMechanism);

	//reset
	comms.reset();
	state.disarm();
	firingMechanism.reset();

	SECTION("Disallowed Continuity Test Should Disarm System")
	{
		comms.pushReadChar(Command_TestContinuity);
		controller.loop(0);

		REQUIRE(continuityTester.wasTested == false);
		REQUIRE(comms.getWrittenChar() == Response_InvalidCommand);

		REQUIRE(state.getState() == State_Ready);

		// flush
		for (int i = 0; i < 100; i++)
			controller.loop(0);

		REQUIRE(firingMechanism.wasFired == false);
	}

	SECTION("Continuity Fail Shouldnt Allow Firing")
	{
		// set continuity fail result
		continuityTester.setResult(false);

		comms.pushReadChar(Command_Arm);
		controller.loop(0);

		REQUIRE(comms.getWrittenChar() == Response_Armed);

		comms.pushReadChar(Command_TestContinuity);
		controller.loop(0);

		REQUIRE(continuityTester.wasTested == true);
		REQUIRE(comms.getWrittenChar() == Response_ContinuityFailed);

		comms.pushReadChar(Command_Fire);
		controller.loop(0);

		REQUIRE(comms.getWrittenChar() == Response_InvalidCommand);

		REQUIRE(state.getState() == State_Ready);

		// flush
		for (int i = 0; i < 100; i++)
			controller.loop(0);

		REQUIRE(firingMechanism.wasFired == false);
	}

	SECTION("Arm + Continuity Pass Should Allow Firing")
	{
		// set continuity fail result
		continuityTester.setResult(true);

		comms.pushReadChar(Command_Arm);
		controller.loop(0);

		REQUIRE(comms.getWrittenChar() == Response_Armed);

		comms.pushReadChar(Command_TestContinuity);
		controller.loop(0);

		REQUIRE(continuityTester.wasTested == true);
		REQUIRE(comms.getWrittenChar() == Response_ContinuityPassed);

		comms.pushReadChar(Command_Fire);
		controller.loop(0);

		REQUIRE(comms.getWrittenChar() == Response_Firing);
		REQUIRE(firingMechanism.wasFired == true);
	}
}
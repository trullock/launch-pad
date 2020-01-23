#include "../../catch.h"
#include "../../mocks/test-comm-channel.h"
#include "../../mocks/test-continuity-tester.h"
#include "../../mocks/test-firing-mechanism.h"
#include "../../mocks/test-state-observer.h"
#include "../../../src/controller.h"

TEST_CASE("State Transitions") {

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

	SECTION("Arming should fail if not interlocked")
	{
		comms.pushReadChar(Command_Arm);
		controller.loop(0);

		REQUIRE(state.getState() == State_Ready);

		// flush
		for (int i = 0; i < 16; i++)
			controller.loop(0);

		REQUIRE(continuityTester.wasTested == false);
		REQUIRE(firingMechanism.wasFired == false);
		REQUIRE(firingMechanism.wasStopped == true);
	}

	SECTION("Arming should succeed when interlocked")
	{
		stateObserver.setInterlockEngaged(true);

		comms.pushReadChar(Command_Arm);
		controller.loop(0);

		REQUIRE(state.getState() == State_Armed);

		// flush
		for (int i = 1; i < 16; i++)
			controller.loop(i);

		REQUIRE(continuityTester.wasTested == false);
		REQUIRE(firingMechanism.wasFired == false);
		REQUIRE(firingMechanism.wasStopped == false);
	}

	SECTION("Disengaging interlock when armed should disarm")
	{
		stateObserver.setInterlockEngaged(true);

		comms.pushReadChar(Command_Arm);
		controller.loop(0);

		stateObserver.setInterlockEngaged(false);

		// flush
		for (int i = 1; i < 16; i++)
			controller.loop(i);

		REQUIRE(state.getState() == State_Ready);

		REQUIRE(continuityTester.wasTested == false);
		REQUIRE(firingMechanism.wasFired == false);
		REQUIRE(firingMechanism.wasStopped == true);
	}

	SECTION("Disengaging interlock when armed and trying to Continuity Test should disarm and not test continuity")
	{
		stateObserver.setInterlockEngaged(true);

		comms.pushReadChar(Command_Arm);
		controller.loop(0);

		stateObserver.setInterlockEngaged(false);
		comms.pushReadChar(Command_TestContinuity);
		controller.loop(1);

		// flush
		for (int i = 2; i < 16; i++)
			controller.loop(i);

		REQUIRE(state.getState() == State_Ready);

		REQUIRE(continuityTester.wasTested == false);
		REQUIRE(firingMechanism.wasFired == false);
		REQUIRE(firingMechanism.wasStopped == true);
	}

	SECTION("Disengaging interlock when ContinuityTested should disarm")
	{
		stateObserver.setInterlockEngaged(true);

		comms.pushReadChar(Command_Arm);
		controller.loop(0);

		continuityTester.setResult(true);
		comms.pushReadChar(Command_TestContinuity);
		controller.loop(1);

		stateObserver.setInterlockEngaged(false);

		// flush
		for (int i = 2; i < 16; i++)
			controller.loop(i);

		REQUIRE(state.getState() == State_Ready);

		REQUIRE(continuityTester.wasTested == true);
		REQUIRE(firingMechanism.wasFired == false);
		REQUIRE(firingMechanism.wasStopped == true);
	}

	SECTION("Disengaging interlock when ContinuityTested and trying to fire should disarm")
	{
		stateObserver.setInterlockEngaged(true);

		comms.pushReadChar(Command_Arm);
		controller.loop(0);

		continuityTester.setResult(true);
		comms.pushReadChar(Command_TestContinuity);
		controller.loop(1);

		comms.pushReadChar(Command_Fire);
		stateObserver.setInterlockEngaged(false);
		controller.loop(2);

		// flush
		for (int i = 3; i < 16; i++)
			controller.loop(i);

		REQUIRE(state.getState() == State_Ready);

		REQUIRE(continuityTester.wasTested == true);
		REQUIRE(firingMechanism.wasFired == false);
		REQUIRE(firingMechanism.wasStopped == true);
	}
}
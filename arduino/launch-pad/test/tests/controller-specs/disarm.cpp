#include "../../catch.h"
#include "../../mocks/test-comm-channel.h"
#include "../../mocks/test-continuity-tester.h"
#include "../../mocks/test-firing-mechanism.h"
#include "../../mocks/test-state-observer.h"
#include "../../../src/controller.h"

TEST_CASE("Disarming") {

	TestCommChannel comms;
	TestContinuityTester continuityTester;
	StateMachine state;
	TestFiringMechanism firingMechanism;
	TestStateObserver stateObserver;

	Controller controller(&comms, &state, &continuityTester, &firingMechanism, &stateObserver);

	//reset
	comms.reset();
	comms.setConnected(true);
	state.disarm();
	firingMechanism.reset();
	stateObserver.setInterlockEngaged(true);

	SECTION("Disarm after Arm should disarm state and force cease-fire")
	{
		comms.pushReadChar(Command_Arm);
		controller.loop(0);

		comms.pushReadChar(Command_Disarm);
		controller.loop(1);

		REQUIRE(state.getState() == State_Ready);

		// flush
		for (int i = 0; i < 16; i++)
			controller.loop(0);

		REQUIRE(continuityTester.wasTested == false);
		REQUIRE(firingMechanism.wasFired == false);
		REQUIRE(firingMechanism.wasStopped == true);
	}

	SECTION("Disarm after Arm+ContinuityTest should disarm state and force cease-fire")
	{
		comms.pushReadChar(Command_Arm);
		controller.loop(0);

		comms.pushReadChar(Command_TestContinuity);
		controller.loop(10);

		comms.pushReadChar(Command_Disarm);
		controller.loop(20);

		REQUIRE(state.getState() == State_Ready);

		// flush
		for (int i = 0; i < 16; i++)
			controller.loop(21 + i);

		REQUIRE(continuityTester.wasTested == true);
		REQUIRE(firingMechanism.wasFired == false);
		REQUIRE(firingMechanism.wasStopped == true);
	}

	SECTION("Disarm during Fire should disarm state and force cease-fire")
	{
		comms.pushReadChar(Command_Arm);
		controller.loop(0);

		comms.pushReadChar(Command_TestContinuity);
		continuityTester.setResult(true);
		controller.loop(10);

		comms.pushReadChar(Command_Fire);
		controller.loop(20);

		comms.pushReadChar(Command_Disarm);
		controller.loop(21); // 1ms is less than the firing duration

		REQUIRE(state.getState() == State_Ready);

		// flush
		for (int i = 0; i < 16; i++)
			controller.loop(22 + i);

		REQUIRE(continuityTester.wasTested == true);
		REQUIRE(firingMechanism.wasFired == true);
		REQUIRE(firingMechanism.wasStopped == true);
	}
}
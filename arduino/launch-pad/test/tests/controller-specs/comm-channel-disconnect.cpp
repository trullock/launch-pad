#include "../../catch.h"
#include "../../mocks/test-comm-channel.h"
#include "../../mocks/test-continuity-tester.h"
#include "../../mocks/test-firing-mechanism.h"
#include "../../mocks/test-state-observer.h"
#include "../../../src/controller.h"

TEST_CASE("Comm channel disconnect") {

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
	continuityTester.setResult(true);

	SECTION("Comm channel disconnect during Armed should disarm")
	{
		comms.pushReadChar(Command_Arm);
		controller.loop(0);

		REQUIRE(comms.getWrittenChar() == Response_Armed);

		comms.setConnected(false);
		controller.loop(1);

		// flush
		for (int i = 0; i < 16; i++)
			controller.loop(1 + i);

		REQUIRE(firingMechanism.wasFired == false);
		
		REQUIRE(comms.getWrittenChar() == Response_Disarmed);
		REQUIRE(state.getState() == State_Disarmed);
	}
	
	SECTION("Comm channel disconnect during Continuity-test-passed should disarm")
	{
		comms.pushReadChar(Command_Arm);
		controller.loop(0);

		REQUIRE(comms.getWrittenChar() == Response_Armed);

		comms.pushReadChar(Command_TestContinuity);
		controller.loop(1);

		REQUIRE(comms.getWrittenChar() == Response_ContinuityPassed);

		comms.setConnected(false);
		controller.loop(2);

		// flush
		for (int i = 0; i < 16; i++)
			controller.loop(2 + i);

		REQUIRE(firingMechanism.wasFired == false);
		
		REQUIRE(comms.getWrittenChar() == Response_Disarmed);
		REQUIRE(state.getState() == State_Disarmed);
	}
}
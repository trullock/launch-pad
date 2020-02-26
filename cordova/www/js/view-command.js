class CommandPage extends Page
{
	constructor() {
		super(document.querySelector('#pgCommand'));
		var me = this;

		this.$btnArm = this.$el.querySelector('button#btnArm');
		this.$btnArm.addEventListener('click', function(e){
			me.requestArm();
		});

		this.$btnTestContinuity = this.$el.querySelector('button#btnTestContinuity');
		this.$btnTestContinuity.addEventListener('click', function (e) {
			network.tcpSend("TestContinuity");
			me.disableAllButtons();
		});

		this.$btnDisarm = this.$el.querySelector('button#btnDisarm');
		this.$btnDisarm.addEventListener('click', function (e) {
			network.tcpSend("Disarm");
			me.disableAllButtons();
		});

		this.$btnFire = this.$el.querySelector('button#btnFire');
		this.$btnFire.addEventListener('click', function (e) {
			network.tcpSend("Fire");
			me.disableAllButtons();
		});

		this.$interlockState = this.$el.querySelector('div.status .interlock');
		this.$interlockStateMessage = this.$interlockState.querySelector('span.state');

		this.$firingMechanism = this.$el.querySelector('div.status .firing-mechanism');
		this.$firingMechanismMessage = this.$firingMechanism.querySelector('span.state');

		this.$padStatus = this.$el.querySelector('div.status .pad-status');
		this.$padStatusMessage = this.$padStatus.querySelector('span.state');

		this.$padVoltage = this.$el.querySelector('div.status .voltage');
		this.$padVoltageMessage = this.$padVoltage.querySelector('span.state');

		this.$commandTimeoutState = this.$el.querySelector('div.status .command-timeout');
		this.$commandTimeoutStateMessage = this.$commandTimeoutState.querySelector('span.state');

		document.addEventListener('volumeupbutton', this.volumeUpButton.bind(this), false);

		window.bus.subscribe('pad state change', function(state){
			me.setState(state);
		});

		this.setState({
			interlockEngaged: false,
			firingMechanismEngaged: false,
			batteryVoltage: 0,
			state: STATE_DISARMED,
			event: 0
		});
	}

	volumeUpButton(e) {
		this.volumeUpButtonPressed = e.direction == 'down';

		if(this.state !== 'PassedContinuityTest')
			return;

		this.passContinuityTest();
	}

	requestArm() {
		var me = this;

		function doArm() {
			bus.publish('console log', 'Sending Arm command');
			network.tcpSend("Arm");
			me.disableAllButtons();
		}

		Fingerprint.isAvailable(function () {
			Fingerprint.show({ 
				title: "Authentication Required",
				description: "Arm Launch Pad" 
			}, doArm);
		}, doArm);
	}

	clearCommandTimeout() {
		if (this.commandTimeoutInterval)
			window.clearInterval(this.commandTimeoutInterval);

		this.commandTimeoutCounter = 0;

		this.setCommandTimeout();
	}

	startCommandTimeout() {
		this.clearCommandTimeout();

		this.commandTimeoutCounter = 20;

		var me = this;
		this.commandTimeoutInterval = window.setInterval(function() {
			if(me.commandTimeoutCounter == 0) {
				me.clearCommandTimeout();
				return;
			}
			
			me.commandTimeoutCounter--;
			me.setCommandTimeout();
		}, 1000);

		this.setCommandTimeout();
	}

	setCommandTimeout() {
		if (this.commandTimeoutCounter == 0)
		{
			this.$commandTimeoutStateMessage.innerText = 'Elapsed';
			this.$commandTimeoutState.classList.remove('green', 'red', 'yellow');
			this.$commandTimeoutState.classList.add('red');
		}
		else if (this.commandTimeoutCounter < 10)
		{
			this.$commandTimeoutStateMessage.innerText = this.commandTimeoutCounter + 's';
			this.$commandTimeoutState.classList.remove('green', 'red', 'yellow');
			this.$commandTimeoutState.classList.add('yellow');
		}
		else
		{
			this.$commandTimeoutStateMessage.innerText = this.commandTimeoutCounter + 's';
			this.$commandTimeoutState.classList.remove('green', 'red', 'yellow');
			this.$commandTimeoutState.classList.add('green');
		}
	}

	setState(state) {
		this.setInterlockState(state.interlockEngaged);
		this.setFiringMechanism(state.firingMechanismEngaged);
		this.setPadVoltage(state.batteryVoltage);

		this.disableAllButtons();

		// Armed || ContinuityTestPassed
		if(state.event === 'A' || state.event === 'C')
		{
			this.startCommandTimeout();
		} 
		// Disarmed || Firing
		else if(state.event === 'D' || state.state === 'F')
		{
			this.clearCommandTimeout();
		}

		if (state.interlockEngaged) {
			if (state.state === STATE_DISARMED)
				this.disarm();
			else if (state.state === STATE_ARMED)
				this.arm();
			else if (state.state === STATE_CONTINUITYTESTPASSED)
				this.passContinuityTest();
			else if (state.state === STATE_FIRING)
				this.fire();
		}
	}

	setInterlockState(engaged)
	{
		if(engaged)
		{
			this.$interlockStateMessage.innerHTML = "Engaged"
			this.$interlockState.classList.remove('disengaged');
			this.$interlockState.classList.add('engaged');
		}
		else
		{
			this.$interlockStateMessage.innerHTML = "Disengaged"
			this.$interlockState.classList.add('disengaged');
			this.$interlockState.classList.remove('engaged');
		}
	}

	setFiringMechanism(engaged) {
		if (engaged) {
			this.$firingMechanismMessage.innerHTML = "Live"
			this.$firingMechanism.classList.add('engaged');
			this.$firingMechanism.classList.remove('disengaged');
		}
		else {
			this.$firingMechanismMessage.innerHTML = "Safe"
			this.$firingMechanism.classList.remove('engaged');
			this.$firingMechanism.classList.add('disengaged');
		}
	}

	setPadVoltage(voltage) {
		this.$padVoltageMessage.innerText = voltage + 'V';
		this.$padVoltage.classList.remove('ok', 'low', 'flat');

		if (voltage > 12) {	
			this.$padVoltage.classList.add('ok');
		}
		else if(voltage > 11.8)
		{
			this.$padVoltage.classList.add('low');
		} else 
		{
			this.$padVoltage.classList.add('flat');
		}
	}

	setPadStatus(status) {
		
	}

	disableAllButtons()
	{
		this.$btnArm.disabled = true;
		this.$btnTestContinuity.disabled = true;
		this.$btnDisarm.disabled = true;
		this.$btnFire.disabled = true;
	}

	disarm()
	{
		this.state = 'Disarmed';

		this.$btnArm.disabled = false;
		this.$padStatus.classList.remove('disarmed', 'armed', 'continuity-test-passed', 'firing');
		this.$padStatus.classList.add('disarmed');
		this.$padStatusMessage.innerText = "Disarmed";
	}

	arm()
	{
		this.state = 'Armed';

		this.$btnTestContinuity.disabled = false;
		this.$btnDisarm.disabled = false;

		this.$padStatus.classList.remove('disarmed', 'armed', 'continuity-test-passed', 'firing');
		this.$padStatus.classList.add('armed');
		this.$padStatusMessage.innerText = "Armed";
	}

	passContinuityTest()
	{
		this.state = 'PassedContinuityTest';

		this.$btnFire.disabled = !this.volumeUpButtonPressed;
		this.$btnDisarm.disabled = false;

		this.$padStatus.classList.remove('disarmed', 'armed', 'continuity-test-passed', 'firing');
		this.$padStatus.classList.add('continuity-test-passed');
		this.$padStatusMessage.innerText = "Passed Continuity Test";
	}

	fire()
	{
		this.state = 'Firing';

		this.$btnDisarm.disabled = false;

		this.$padStatus.classList.remove('disarmed', 'armed', 'continuity-test-passed', 'firing');
		this.$padStatus.classList.add('firing');
		this.$padStatusMessage.innerText = "Firing";
	}
}
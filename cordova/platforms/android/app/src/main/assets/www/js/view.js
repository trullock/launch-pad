class Page
{
	constructor($el)
	{
		this.$el = $el;
	}

	show() {
		this.$el.classList.remove('hidden');
	}

	hide() {
		this.$el.classList.add('hidden');
	}
};

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

		this.$commandTimeoutState = this.$el.querySelector('div.status .command-timeout');
		this.$commandTimeoutStateMessage = this.$commandTimeoutState.querySelector('span.state');

		window.bus.subscribe('state change', function(state){
			me.setState(state);
		});

		this.setState({
			interlockEngaged: false,
			firingMechanismEngaged: false,
			state: STATE_DISARMED,
			event: 0
		});
	}

	requestArm() {
		var me = this;

		function doArm() {
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
			me.commandTimeoutCounter--;
			me.setCommandTimeout();
		}, 1000);

		this.setCommandTimeout();
	}

	setCommandTimeout() {
		if (this.commandTimeoutCounter > 0)
		{
			this.$commandTimeoutStateMessage.innerText = this.commandTimeoutCounter + 's';
			this.$commandTimeoutState.classList.remove('red');
			this.$commandTimeoutState.classList.add('green');
		}
		else
		{
			this.$commandTimeoutStateMessage.innerText = 'Elapsed';
			this.$commandTimeoutState.classList.remove('green');
			this.$commandTimeoutState.classList.add('red');
		}
	}

	setState(state) {
		this.setInterlockState(state.interlockEngaged);
		this.setFiringMechanism(state.firingMechanismEngaged);

		this.disableAllButtons();

		// Armed || ContinuityTestPassed
		if(state.event === 'A' || state.event === 'C')
		{
			this.startCommandTimeout();
		} 
		// Disarmed
		else if(state.event === 'D')
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
			this.$interlockStateMessage.innerText = "Engaged ✔️"
			this.$interlockState.classList.remove('red');
			this.$interlockState.classList.add('green');
		}
		else
		{
			this.$interlockStateMessage.innerText = "Disengaged ❌"
			this.$interlockState.classList.add('red');
			this.$interlockState.classList.remove('green');
		}
	}

	setFiringMechanism(engaged) {
		if (engaged) {
			this.$firingMechanismMessage.innerText = "Engaged 🔥"
			this.$firingMechanism.classList.add('red');
			this.$firingMechanism.classList.remove('green');
		}
		else {
			this.$firingMechanismMessage.innerText = "Disengaged ❌"
			this.$firingMechanism.classList.remove('red');
			this.$firingMechanism.classList.add('green');
		}
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
		this.$btnArm.disabled = false;

		this.$padStatus.classList.remove('red', 'green', 'yellow');
		this.$padStatusMessage.innerText = "Disarmed";
	}

	arm()
	{
		this.$btnTestContinuity.disabled = false;
		this.$btnDisarm.disabled = false;

		this.$padStatus.classList.remove('red', 'green', 'yellow');
		this.$padStatus.classList.add('green');
		this.$padStatusMessage.innerText = "Armed";
	}

	passContinuityTest()
	{
		this.$btnFire.disabled = false;
		this.$btnDisarm.disabled = false;

		this.$padStatus.classList.remove('red', 'green', 'yellow');
		this.$padStatus.classList.add('yellow');
		this.$padStatusMessage.innerText = "Passed Continuity Test";
	}

	fire()
	{
		this.$btnDisarm.disabled = false;

		this.$padStatus.classList.remove('red', 'green', 'yellow');
		this.$padStatus.classList.add('red');
		this.$padStatusMessage.innerText = "Firing";
	}
}

class ConsolePage extends Page
{
	constructor() {
		super(document.querySelector('#pgConsole'));
		this.$console = this.$el.querySelector('pre');
		
		var me = this;
		window.bus.subscribe('console log', function(message){
			me.write(message);
		});
	}

	write(message) {
		this.$console.innerText += (new Date()).toISOString() + ": " + data + "\r\n";
		this.$console.scrollTop = this.$console.scrollHeight;
	}
}

var view = (function() {

	let pgCommand = new CommandPage();
	let pgConsole = new ConsolePage();

	function hideAllPages(){
		pgCommand.hide();
		pgConsole.hide();
	}

	return {

		pages: {

			showCommand: function(){
				hideAllPages();
				pgCommand.show();
			},

			showConsole: function(){
				hideAllPages();
				pgConsole.show();
			}
		}
	};

})();
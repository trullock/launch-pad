function startNetworking() {
	network.listenForUdpBeacon().then(remoteAddress => {
		bus.publish('console log', 'Pad found: ' + remoteAddress);
		bus.publish('pad located', remoteAddress);
		return network.tcpConnect(remoteAddress);
	}).then(function (result) {
		bus.publish('console log', 'Connected to pad');
		bus.publish('pad connected');
		return network.tcpSend('Hello');
	}).then(function () {
		
	}).catch(function(e){
		console.error(e);
	});
}

var app = {
    initialize: function() {
		document.addEventListener('deviceready', this.onDeviceReady.bind(this), false);

		document.addEventListener('pause', function(){
			//network.disconnectUdp();
			//network.disconnectTcp();
		}, false);
		
		document.addEventListener('resume', function (){
			//navigator.splashscreen.show();
			//startNetworking();
		}, false);
    },

    onDeviceReady: function() {
		network.init();

		network.onTcpReceive = function (str) {
			var event = str[0];
			var state = str[1];
			var interlockEngaged = str[2] == '1';
			var firingMechanismEngaged = str[3] == '1';

			switch(event){
				case 'A':
					bus.publish('console log', 'Pad Armed');
					break;
				case 'C':
					bus.publish('console log', 'Pad Passed-Continuity-Test');
					break;
				case 'D':
					bus.publish('console log', 'Pad Disarmed');
					break;
				case 'F':
					bus.publish('console log', 'Pad Firing');
					break;
			}

			window.bus.publish('pad state change', {
				state: state,
				interlockEngaged: interlockEngaged,
				firingMechanismEngaged: firingMechanismEngaged,
				event: event
			});
		};

		network.onTcpReceiveError = function(e) {
			bus.publish('pad disconnected');
			startNetworking();
		};

		bus.publish('pad disconnected');

		startNetworking();

		navigator.splashscreen.hide();
    }
};

app.initialize();
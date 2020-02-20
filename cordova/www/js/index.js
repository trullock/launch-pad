function startNetworking() {
	network.listenForUdpBeacon().then(remoteAddress => {
		console.log(remoteAddress);
		return network.tcpConnect(remoteAddress);
	}).then(function (result) {
		return network.tcpSend('Hello');
	}).then(function () {
		navigator.splashscreen.hide();
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
		var me = this;
		
		network.onTcpReceive = function (str) {
			var event = str[0];
			var state = str[1];
			var interlockEngaged = str[2] == '1';
			var firingMechanismEngaged = str[3] == '1';
			window.bus.publish('state change', {
				state: state,
				interlockEngaged: interlockEngaged,
				firingMechanismEngaged: firingMechanismEngaged,
				event: event
			});
		};

		network.onTcpReceiveError = function() {
			navigator.splashscreen.show();
			startNetworking();
		};

		startNetworking();
    }
};

app.initialize();
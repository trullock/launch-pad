var app = {
    initialize: function() {
        document.addEventListener('deviceready', this.onDeviceReady.bind(this), false);
    },

    onDeviceReady: function() {
		var me = this;

		network.listenForUdpBeacon().then(remoteAddress => {
			console.log(remoteAddress);

			network.onTcpReceive = function (str) {
				var event = str[0];
				var state = str[1];
				var interlockEngaged = str[2] == '1';
				window.bus.publish('state change', {
					state: state,
					interlockEngaged: interlockEngaged,
					event: event
				});
			}

			return network.tcpConnect(remoteAddress);
		}).then(function(result){
			return network.tcpSend('Hello');
		}).then(function(){
			navigator.splashscreen.hide();
		});
    }
};

app.initialize();
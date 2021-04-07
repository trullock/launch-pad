var controller = (function(){

	return {
		autoConnect: function() {
			var me = this;

			bus.publish('console log', 'remote', 'Searching for pad');
			
			network.listenForUdpBeacon().then(remoteAddress => {
				bus.publish('console log', 'remote', 'Pad found: ' + remoteAddress);
				bus.publish('pad located', remoteAddress);
				return me.connect(remoteAddress);
			}).catch(function (e) {
				bus.publish('console error', 'remote', 'Error autoconnecting', e);
			});
		}

		, connect: function(remoteAddress) {
			bus.publish('console log', 'remote', 'Connecting to pad: ' + remoteAddress);

			return network.tcpConnect(remoteAddress).then(function (result) {
				bus.publish('console log', 'remote', 'Connected to pad: ' + remoteAddress);
				bus.publish('pad connected');
				return network.tcpSend('Hello');
			}).catch(function (e) {
				bus.publish('console error', 'remote', 'Error connecting to pad: ' + remoteAddress, e);
			});
		}

		, init: function(){
			var me = this;

			network.onTcpReceive = function (str) {
				var event = str[0];
				var state = str[1];
				var interlockEngaged = str[2] == '1';
				var firingMechanismEngaged = str[3] == '1';
				var batteryVoltage = interlockEngaged ? parseInt(str.substr(4, 3), 10) / 10.0 : 0;

				switch (event) {
					case 'A':
						bus.publish('console log', 'pad', 'Pad Armed');
						break;
					case 'C':
						bus.publish('console log', 'pad', 'Pad Passed-Continuity-Test');
						break;
					case 'D':
						bus.publish('console log', 'pad', 'Pad Disarmed');
						break;
					case 'F':
						bus.publish('console log', 'pad', 'Pad Firing');
						break;
				}

				window.bus.publish('pad state update', {
					state: state,
					interlockEngaged: interlockEngaged,
					firingMechanismEngaged: firingMechanismEngaged,
					batteryVoltage: batteryVoltage,
					event: event
				});
			};

			network.onTcpReceiveError = function (e) {
				bus.publish('pad disconnected');

				if(me.connectionMode === 'auto')
				{
					bus.publish('console log', 'remote', 'Automatically attempting reconnect');
					me.autoConnect();
				}
			};

			// Connect
			bus.subscribe('pad connect', function (remoteAddress) {
				me.connect(remoteAddress);
			});
			bus.subscribe('pad connected', function () {
				me.padConnected = true;
			});

			// Disconnect
			bus.subscribe('pad disconnect', function () {
				network.disconnectTcp().then(_ => {
					bus.publish('pad disconnected');
				});
			});
			bus.subscribe('pad disconnected', function () {
				me.padConnected = false;
			});


			bus.subscribe('connection-mode changed', function (mode) {
				me.connectionMode = mode;

				if(!me.padConnected && mode === 'auto')
					me.autoConnect();
			});
		}

		, start: function(){
			bus.publish('pad dislocated');
			bus.publish('pad disconnected');
			bus.publish('connection-mode changed', 'auto');
		}

	};
})();
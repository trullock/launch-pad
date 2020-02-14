var app = {
    initialize: function() {
        document.addEventListener('deviceready', this.onDeviceReady.bind(this), false);
    },

    onDeviceReady: function() {
		var me = this;

		me.pgConsole = document.querySelector('#pgConsole');
		me.txtConsole = me.pgConsole.querySelector('pre');

		document.querySelector('#btnDiscoverPad').addEventListener('click', function(e){
			e.preventDefault();

			chrome.sockets.udp.create({}, function (socketInfo) {
				me.udpSocketId = socketInfo.socketId;

				chrome.sockets.udp.onReceive.addListener(info => me.udpReceive(info));
				chrome.sockets.udp.bind(me.udpSocketId, "0.0.0.0", 4321, function (result) {
					if (result < 0) {
						console.log("Error binding socket.");
						return;
					}
				});
			});
		});

		document.querySelector('#btnConnect').addEventListener('click', function (e) {
			e.preventDefault();

			chrome.sockets.tcp.create({}, function (socketInfo) {
				me.tcpSocketId = socketInfo.socketId;
				chrome.sockets.tcp.setKeep
				chrome.sockets.tcp.onReceive.addListener(info => me.tcpReceive(info));
				chrome.sockets.udp.bind(me.socketId, "0.0.0.0", 4321, function (result) {
					if (result < 0) {
						console.log("Error binding socket.");
						return;
					}
				});
			});
		});


    },

	udpReceive: function (info) {
		if (info.socketId !== this.udpSocketId)
			return;
		console.log(String.fromCharCode.apply(null, new Uint8Array(info.data)));
		this.consoleLog(String.fromCharCode.apply(null, new Uint8Array(info.data)))
	},

	consoleLog: function(data){
		this.txtConsole.innerText += (new Date()).toISOString() + ": " + data + "\r\n";
		this.txtConsole.scrollTop = this.txtConsole.scrollHeight;
	}
};

app.initialize();
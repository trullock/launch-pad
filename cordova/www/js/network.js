var network = (function(){

	let udpSocketId = null;
	let tcpSocketId = null;
	let udpListenResolver = null;

	function ab2str(buf) {
		return String.fromCharCode.apply(null, new Uint8Array(buf));
	}

	function str2ab(str) {
		var buf = new ArrayBuffer(str.length);
		var bufView = new Uint8Array(buf);
		for (var i = 0, strLen = str.length; i < strLen; i++)
			bufView[i] = str.charCodeAt(i);
		return buf;
	}

	function udpReceive (info) {
		if (info.socketId !== udpSocketId)
			return;

		let data = ab2str(info.data);
		//console.log("UDP Received: " + data);
		
		if(udpListenResolver) {
			if(data === "LaunchPad:Hello"){
				udpListenResolver(info.remoteAddress);
				udpListenResolver = null;
			}
		}
	}

	function tcpReceive(info) {
		if (info.socketId !== tcpSocketId)
			return;

		let data = String.fromCharCode.apply(null, new Uint8Array(info.data));
		//console.log("TCP Received: " + data);

		// Heartbeat response
		obj.tcpSend("Hello");

		if(obj.onTcpReceive)
			obj.onTcpReceive(data);
	}

	function tcpReceiveError(info) {
		if (info.socketId !== tcpSocketId)
			return;

		console.error("TCP Error: ");
		console.error(info);

		// TODO: this may never invoke the callback
		chrome.sockets.tcp.close(tcpSocketId, function(info){
			if (obj.onTcpReceiveError)
				obj.onTcpReceiveError(info);
		});
	}

	function beginUdpListen () {
		return new Promise((resolve, reject) => {
			chrome.sockets.udp.create({}, function (socketInfo) {
				udpSocketId = socketInfo.socketId;

				chrome.sockets.udp.bind(udpSocketId, "0.0.0.0", 4321, function (result) {
					if (result < 0) {
						console.error("Error binding socket");
						console.error(result);

						reject(Error("Error bidning socket"));
						return;
					}

					udpListenResolver = resolve;
				});
			});
		});
	}

	function beginTcpListen (host) {
		//console.log('Beginning TCP connection to ' + host);
		return new Promise((resolve, reject) => {
			chrome.sockets.tcp.create({}, function (socketInfo) {
				tcpSocketId = socketInfo.socketId;
				chrome.sockets.tcp.connect(tcpSocketId, host, 4321, function (result) {
					if (result < 0) {
						console.error("Error connecting");
						console.error(result);

						reject(Error("Error connecting"));
						return;
					}
					resolve(result);
				});
			});
		});
	}

	function tcpSend(data){
		//console.log("TCP Send: " + data);
		return new Promise((resolve, reject) => {
			var buff = str2ab(data + '\0');
			chrome.sockets.tcp.send(tcpSocketId, buff, function (info) {
				if (info.resultCode < 0)
					reject(info);
				else
					resolve(info);
			});
		});
	};

	function disconnectUdp() {
		return new Promise((resolve, reject) => {
			if (udpSocketId) {
				try {
					chrome.sockets.udp.close(udpSocketId, function () {
						resolve();
					})
				} catch (e) {
					resolve();
				}
			}
			else {
				resolve();
			}
		});
	}

	function disconnectTcp() {
		return new Promise((resolve, reject) => {
			if (tcpSocketId) {
				try {
					// callback is not called in error scenarios, so we will just exec this async and not care what happens to the previous socket
					chrome.sockets.tcp.close(tcpSocketId, function () { });
					tcpSocketId = null;
					resolve();
				} catch (e) {
					resolve();
				}
			}
			else {
				resolve();
			}
		})
	}


	var obj = {

		init: function(){
			chrome.sockets.udp.onReceive.addListener(info => udpReceive(info));

			chrome.sockets.tcp.onReceive.addListener(info => tcpReceive(info));
			chrome.sockets.tcp.onReceiveError.addListener(info => tcpReceiveError(info));
		},

		listenForUdpBeacon: function(){
			return obj.disconnectUdp().then(beginUdpListen);
		},

		tcpConnect: function (host) {
			return obj.disconnectTcp().then(_ => {
				return beginTcpListen(host);
			});
		},

		tcpSend: tcpSend,
		disconnectUdp: disconnectUdp,
		disconnectTcp: disconnectTcp		
	}

	return obj;
})();
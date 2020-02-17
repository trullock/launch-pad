var network = (function(){


	let udpSocketId = null;
	let tcpSocketId = null;
	let udpListenResolver = null;

	function ab2str(buf) {
		return String.fromCharCode.apply(null, new Uint8Array(buf));
	}

	function str2ab(str) {
		var buf = new ArrayBuffer(str.length); // 1 bytes for each char
		var bufView = new Uint8Array(buf);
		for (var i = 0, strLen = str.length; i < strLen; i++) {
			bufView[i] = str.charCodeAt(i);
		}
		return buf;
	}

	function udpReceive (info) {
		if (info.socketId !== udpSocketId)
			return;

		let data = ab2str(info.data);
		//console.log(data);
		
		if(udpListenResolver){
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
		console.log("TCP Received: " + data);
		
		if(obj.onTcpReceive)
			obj.onTcpReceive(data);
	}

	function tcpReceiveError(info) {
		if (info.socketId !== tcpSocketId)
			return;

		let data = String.fromCharCode.apply(null, new Uint8Array(info.data));
		console.log("Error: " + data);
	}

	var obj = {

		listenForUdpBeacon: function(){
			return new Promise((resolve, reject) => {
				chrome.sockets.udp.create({}, function (socketInfo) {
					udpSocketId = socketInfo.socketId;

					chrome.sockets.udp.onReceive.addListener(info => udpReceive(info));
					chrome.sockets.udp.bind(udpSocketId, "0.0.0.0", 4321, function (result) {
						if (result < 0) {
							console.log("Error binding socket.");
							reject(Error("Error bidning socket"));
							return;
						}

						udpListenResolver = resolve;
					});
				}); 
				
			});
		},

		tcpConnect: function (host) {
			return new Promise((resolve, reject) => {
				chrome.sockets.tcp.create({}, function (socketInfo) {
					tcpSocketId = socketInfo.socketId;
					chrome.sockets.tcp.onReceive.addListener(info => tcpReceive(info));
					chrome.sockets.tcp.onReceiveError.addListener(info => tcpReceiveError(info));
					chrome.sockets.tcp.connect(tcpSocketId, host, 4321, function (result) {
						if (result < 0) {
							console.log("Error connecting");
							reject(Error("Error connecting"));
							return;
						}

						console.log('tcp connected');
						resolve(result);

						// heartbeat
						window.setInterval(function(){
							chrome.sockets.tcp.send(tcpSocketId, str2ab("Hello\0"), function(info){
								//console.log(info);
							});
						}, 1000);
					});
				});
			});
		},

		tcpSend: function(data){
			console.log("TCP Send: " + data);
			return new Promise((resolve, reject) => {
				var buff = str2ab(data + '\0');
				chrome.sockets.tcp.send(tcpSocketId, buff, function (info) {
					if(info.resultCode < 0)
						reject(info);
					else
						resolve(info);
				});
			})
		}

	};

	return obj;
})();
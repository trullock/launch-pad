class SettingsPage extends Page {
	constructor() {
		super(document.querySelector('#pgSettings'));

		function lol(){

			
			serial.requestPermission(function () {
				serial.open({
					baudRate: 115200
				}, function () {
					serial.write('1');
				});

				serial.registerReadCallback(
					function success(data) {
						bus.publish('console log', String.fromCharCode.apply(null, new Uint8Array(data)));
					},
					function error() {
						new Error("Failed to register read callback");
					});
			});
		}
	}
}
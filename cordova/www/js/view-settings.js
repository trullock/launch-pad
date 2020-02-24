class SettingsPage extends Page {
	constructor() {
		super(document.querySelector('#pgSettings'));

		this.$btnConnect = this.$el.querySelector('#btnSerialConnect');
		this.$btnConnect.addEventListener('click', function(){
			serial.requestPermission(function () {
				serial.open({
					baudRate: 115200
				}, function () {
					serial.write('1');
				});

				serial.registerReadCallback(
					function success(data) {
						bus.publish('console log', "Serial: " + String.fromCharCode.apply(null, new Uint8Array(data)));
					},
					function error() {
						bus.publish('console error', new Error("Failed to register Serial read callback"));
					}
				);
			});
		});
	}
}
class ConsolePage extends Page
{
	constructor() {
		super(document.querySelector('#pgConsole'));
		this.$console = this.$el.querySelector('pre');
		
		var me = this;
		window.bus.subscribe('console log', function(message){
			me.log(message);
		});

		window.bus.subscribe('console error', function (message, e) {
			me.error(message, e);
		});
	}

	log(message) {
		console.log(message);

		var now = new Date();
		this.$console.innerHTML += now.toLocaleTimeString() + ": " + message + "\r\n";
		this.$console.scrollTop = this.$console.scrollHeight;
	}

	error(message, e) {
		console.error(message);
		console.error(e)

		var now = new Date();
		this.$console.innerHTML += now.toLocaleTimeString() + ": " + message + "\r\n" + e + "\r\n";
		this.$console.scrollTop = this.$console.scrollHeight;
	}
}

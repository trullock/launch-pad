class ConsolePage extends Page
{
	constructor() {
		super(document.querySelector('#pgConsole'));
		this.$console = this.$el.querySelector('pre');
		
		var me = this;
		window.bus.subscribe('console log', function(source, message){
			me.log(source, message);
		});

		window.bus.subscribe('console error', function (source, message, e) {
			me.error(source, message, e);
		});
	}

	getSourceClass(source){
		switch(source){
			case 'pad':
			case 'remote':
				return source;
			default:
				return '';
		}
	}

	log(source, message) {
		console.log(message);

		var now = new Date();
		this.$console.innerHTML += '<span class="time">' + now.toLocaleTimeString() + ':</span> <span class="log ' + this.getSourceClass(source) + '">' + message + '</span>\r\n';
		this.$console.scrollTop = this.$console.scrollHeight;
	}

	error(source, message, e) {
		console.error(message);
		console.error(e)

		var now = new Date();
		this.$console.innerHTML += '<span class="time">' + now.toLocaleTimeString() + ':</span> <span class="error ' + this.getSourceClass(source) + '">' + message + '</span>\r\n';
		this.$console.innerHTML += '<span class="time">' + now.toLocaleTimeString() + ':</span> <span class="error ' + this.getSourceClass(source) + '">' + e + '</span>\r\n';
		this.$console.scrollTop = this.$console.scrollHeight;
	}
}

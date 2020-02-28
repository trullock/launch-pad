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

		bus.subscribe('connection-mode changed', function(mode){
			me.log('remote', 'Connection mode changed to: ' + mode);
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

	getSourceEmoji(source) {
		switch (source) {
			case 'pad':
				return '&#x1F680;';
			case 'remote':
				return '&#x1F4F1;';
			default:
				return '';
		}
	}

	log(source, message) {
		console.log(message);

		var now = new Date();
		this.$console.innerHTML += this.getSourceEmoji(source) + '<span class="time">' + now.toISOString().substr(11, 12) + ':</span> <span class="log ' + this.getSourceClass(source) + '">' + message + '</span>\r\n';
		this.$console.scrollTop = this.$console.scrollHeight;
	}

	error(source, message, e) {
		console.error(message);
		if(e)
			console.error(e)

		var now = new Date();
		this.$console.innerHTML += this.getSourceEmoji(source) + '<span class="time">' + now.toISOString().substr(11, 12) + ':</span> <span class="error ' + this.getSourceClass(source) + '">' + message + '</span>\r\n';
		if(e)
			this.$console.innerHTML += this.getSourceEmoji(source) + '<span class="time">' + now.toISOString().substr(11, 12) + ':</span> <span class="error ' + this.getSourceClass(source) + '">' + e + '</span>\r\n';
		this.$console.scrollTop = this.$console.scrollHeight;
	}
}

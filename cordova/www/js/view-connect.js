class ConnectPage extends Page {
	constructor() {
		super(document.querySelector('#pgConnect'));

		this.$locationState = this.$el.querySelector('div.status .location');
		this.$locationStateMessage = this.$locationState.querySelector('span.state');
		
		var me = this;

		bus.subscribe('pad located', function (remoteAddress){
			me.$locationState.classList.remove('disengaged');
			me.$locationState.classList.add('engaged');
			me.$locationStateMessage.innerText = remoteAddress;
		});

		bus.subscribe('pad disconnected', function (){
			me.$locationState.classList.add('disengaged');
			me.$locationState.classList.remove('engaged');
			me.$locationStateMessage.innerText = "0.0.0.0";
		});
	}
}
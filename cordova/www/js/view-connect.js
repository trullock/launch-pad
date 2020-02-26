class ConnectPage extends Page {
	constructor() {
		super(document.querySelector('#pgConnect'));

		this.$locationState = this.$el.querySelector('div.status .location');
		this.$locationStateMessage = this.$locationState.querySelector('span.state');

		this.$connState = this.$el.querySelector('div.status .conn-status');
		this.$connStateMessage = this.$connState.querySelector('span.state');

		this.$btnTcpDisconnect = this.$el.querySelector('#btnTcpDisconnect');
		this.$btnTcpConnect = this.$el.querySelector('#btnTcpConnect');

		this.$rbTcpConnModeAuto = this.$el.querySelector('#rbTcpConnModeAuto');
		this.$rbTcpConnModeAuto.addEventListener('click', function(){
			bus.publish('connection-mode changed', 'auto');
		})
		this.$rbTcpConnModeManual = this.$el.querySelector('#rbTcpConnModeManual');
		this.$rbTcpConnModeManual.addEventListener('click', function () {
			bus.publish('connection-mode changed', 'manual');
		})
		var me = this;


		bus.subscribe('connection-mode changed', function (mode) {
			if (mode === 'auto')
			{
				me.$rbTcpConnModeAuto.checked = true;
				me.$btnTcpConnect.disabled = true;
				me.$btnTcpDisconnect.disabled = true;
			}
			else
			{
				me.$rbTcpConnModeManual.checked = true;
				me.$btnTcpConnect.disabled = false;
				me.$btnTcpDisconnect.disabled = false;
			}
		});

		bus.subscribe('pad located', function (remoteAddress){
			me.$locationState.classList.remove('unknown', 'found');
			me.$locationState.classList.add('found');
			me.$locationStateMessage.innerText = remoteAddress;
		});

		bus.subscribe('pad connected', function (){
			me.$connState.classList.remove('connected', 'disconnected');
			me.$connState.classList.add('connected');
			me.$connStateMessage.innerText = "Connected";
		});

		bus.subscribe('pad disconnected', function () {
			me.$locationState.classList.remove('unknown', 'found');
			me.$locationState.classList.add('unknown');
			me.$locationStateMessage.innerText = "0.0.0.0";

			me.$connState.classList.remove('connected', 'disconnected');
			me.$connState.classList.add('disconnected');
			me.$connStateMessage.innerText = "Disconnected";
		});
	}
}
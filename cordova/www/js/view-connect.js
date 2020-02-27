class ConnectPage extends Page {
	constructor() {
		super(document.querySelector('#pgConnect'));

		this.$locationState = this.$el.querySelector('div.status .location');
		this.$locationStateMessage = this.$locationState.querySelector('span.state');

		this.$connState = this.$el.querySelector('div.status .conn-status');
		this.$connStateMessage = this.$connState.querySelector('span.state');

		this.$btnTcpDisconnect = this.$el.querySelector('#btnTcpDisconnect');
		this.$btnTcpDisconnect.addEventListener('click', function(){
			bus.publish('pad disconnect');
		});

		this.$btnTcpConnect = this.$el.querySelector('#btnTcpConnect');
		this.$btnTcpConnect.addEventListener('click', function () {
			bus.publish('pad connect', me.$txtTcpAddress.value);
		});

		this.$rbTcpConnModeAuto = this.$el.querySelector('#rbTcpConnModeAuto');
		this.$rbTcpConnModeAuto.addEventListener('click', function(){
			bus.publish('connection-mode changed', 'auto');
		})

		this.$rbTcpConnModeManual = this.$el.querySelector('#rbTcpConnModeManual');
		this.$rbTcpConnModeManual.addEventListener('click', function () {
			bus.publish('connection-mode changed', 'manual');
		});
		
		this.$txtTcpAddress = this.$el.querySelector('#txtTcpAddress');


		var me = this;


		bus.subscribe('connection-mode changed', function (mode) {
			me.connectionMode = mode;

			if (mode === 'auto')
			{
				me.$rbTcpConnModeAuto.checked = true;
				me.$btnTcpConnect.disabled = true;
				me.setDisconnectButtonState();
				me.$txtTcpAddress.disabled = true;
			}
			else
			{
				me.$rbTcpConnModeManual.checked = true;
				me.$btnTcpConnect.disabled = false;
				me.setDisconnectButtonState();
				me.$txtTcpAddress.disabled = false;
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

			me.padConnected = true;

			me.setDisconnectButtonState();
		});

		bus.subscribe('pad disconnected', function () {
			me.$connState.classList.remove('connected', 'disconnected');
			me.$connState.classList.add('disconnected');
			me.$connStateMessage.innerText = "Disconnected";

			me.padConnected = false;

			me.setDisconnectButtonState();
		});
	}

	setDisconnectButtonState() {
		this.$btnTcpDisconnect.disabled = !this.padConnected || this.connectionMode !== 'manual';
	}
}
(function() {

	let pgConnect = new ConnectPage();
	let pgCommand = new CommandPage();
	let pgConsole = new ConsolePage();
	let pgSettings = new SettingsPage();
	let currentPage = 'command';

	function hideAllPages(){
		pgConnect.hide();
		pgCommand.hide();
		pgConsole.hide();
		pgSettings.hide();
	}

	let btnConnect = document.querySelector('#btnConnect');
	btnConnect.addEventListener('click', function () {
		hideAllPages();
		pgConnect.show();
		currentPage = 'connect';
	});

	let btnCommand = document.querySelector('#btnCommand');
	btnCommand.addEventListener('click', function(){
		hideAllPages();
		pgCommand.show();
		currentPage = 'command';
	});

	let btnConsole = document.querySelector('#btnConsole');
	btnConsole.addEventListener('click', function () {
		hideAllPages();
		pgConsole.show();
		currentPage = 'console';
	});

	let btnSettings = document.querySelector('#btnSettings');
	btnSettings.addEventListener('click', function () {
		hideAllPages();
		pgSettings.show();
		currentPage = 'settings';
	});

	bus.subscribe('pad connected', function(){
		if(currentPage == 'connect'){
			hideAllPages();
			pgCommand.show();
			currentPage = 'command';
		}

		btnCommand.disabled = false;
	});

	bus.subscribe('pad disconnected', function () {
		if(currentPage == 'command'){
			hideAllPages();
			pgConnect.show();
			currentPage = 'connect';
		}

		btnCommand.disabled = true;
	});
})();
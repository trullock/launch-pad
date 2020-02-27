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

		btnConnect.classList.remove('current');
		btnCommand.classList.remove('current');
		btnConsole.classList.remove('current');
		btnSettings.classList.remove('current');
	}

	let btnConnect = document.querySelector('#btnConnect');
	btnConnect.addEventListener('click', function () {
		showConnect();
	});

	let btnCommand = document.querySelector('#btnCommand');
	btnCommand.addEventListener('click', function(){
		showCommand();
	});

	let btnConsole = document.querySelector('#btnConsole');
	btnConsole.addEventListener('click', function () {
		showConsole();
	});

	let btnSettings = document.querySelector('#btnSettings');
	btnSettings.addEventListener('click', function () {
		showSettings();
	});

	function showConnect(){
		hideAllPages();
		pgConnect.show();
		currentPage = 'connect';
		btnConnect.classList.add('current');
	}

	function showCommand() {
		hideAllPages();
		pgCommand.show();
		currentPage = 'command';
		btnCommand.classList.add('current');
	}

	function showConsole() {
		hideAllPages();
		pgConsole.show();
		currentPage = 'console';
		btnConsole.classList.add('current');
	}

	function showSettings() {
		hideAllPages();
		pgSettings.show();
		currentPage = 'settings';
		btnSettings.classList.add('current');
	}

	bus.subscribe('pad connected', function(){
		if(currentPage == 'connect')
			showCommand();

		btnCommand.disabled = false;
	});

	bus.subscribe('pad disconnected', function () {
		if(currentPage == 'command')
			showConnect();
		
		btnCommand.disabled = true;
	});
})();
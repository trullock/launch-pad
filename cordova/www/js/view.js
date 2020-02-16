class Page
{
	constructor($el)
	{
		this.$el = $el;
	}

	show() {
		this.$el.classList.remove('hidden');
	}

	hide() {
		this.$el.classList.add('hidden');
	}
};

class LoadingPage extends Page
{
	constructor() {
		super(document.querySelector('#pgLoading'));
	}
}

class CommandPage extends Page
{
	constructor() {
		super(document.querySelector('#pgCommand');)
	}

	
}

class ConsolePage extends Page
{
	constructor() {
		super(document.querySelector('#pgConsole'));
		this.$console = this.$el.querySelector('pre');
	}

	write(message) {
		this.$console.innerText += (new Date()).toISOString() + ": " + data + "\r\n";
		this.$console.scrollTop = this.$console.scrollHeight;
	}
}

var view = (function() {

	let pgLoading = new LoadingPage();
	let pgCommand = new CommandPage();
	let pgConsole = new ConsolePage();

	function hideAllPages(){
		pgLoading.hide();
		pgCommand.hide();
		pgConsole.hide();
	}

	return {

		pages: {
				
			showLoading: function(){
				hideAllPages();
				pgLoading.show();
			},

			showCommand: function(){
				hideAllPages();
				pgCommand.show();
			},

			showConsole: function(){
				hideAllPages();
				pgConsole.show();
			}
		}
	};

})();
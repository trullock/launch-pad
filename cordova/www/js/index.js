document.addEventListener('deviceready', function () {
	network.init();
	controller.init();
	controller.start();
	
	navigator.splashscreen.hide();
}, false);

document.addEventListener('pause', function () {

}, false);

document.addEventListener('resume', function () {

}, false);
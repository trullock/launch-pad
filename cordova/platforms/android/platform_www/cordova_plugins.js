cordova.define('cordova/plugin_list', function(require, exports, module) {
  module.exports = [
    {
      "id": "cordova-plugin-chrome-apps-common.events",
      "file": "plugins/cordova-plugin-chrome-apps-common/events.js",
      "pluginId": "cordova-plugin-chrome-apps-common",
      "clobbers": [
        "chrome.Event"
      ]
    },
    {
      "id": "cordova-plugin-chrome-apps-common.errors",
      "file": "plugins/cordova-plugin-chrome-apps-common/errors.js",
      "pluginId": "cordova-plugin-chrome-apps-common"
    },
    {
      "id": "cordova-plugin-chrome-apps-common.stubs",
      "file": "plugins/cordova-plugin-chrome-apps-common/stubs.js",
      "pluginId": "cordova-plugin-chrome-apps-common"
    },
    {
      "id": "cordova-plugin-chrome-apps-common.helpers",
      "file": "plugins/cordova-plugin-chrome-apps-common/helpers.js",
      "pluginId": "cordova-plugin-chrome-apps-common"
    },
    {
      "id": "cordova-plugin-chrome-apps-sockets-udp.sockets.udp",
      "file": "plugins/cordova-plugin-chrome-apps-sockets-udp/sockets.udp.js",
      "pluginId": "cordova-plugin-chrome-apps-sockets-udp",
      "clobbers": [
        "chrome.sockets.udp"
      ]
    },
    {
      "id": "cordova-plugin-chrome-apps-sockets-tcp.sockets.tcp",
      "file": "plugins/cordova-plugin-chrome-apps-sockets-tcp/sockets.tcp.js",
      "pluginId": "cordova-plugin-chrome-apps-sockets-tcp",
      "clobbers": [
        "chrome.sockets.tcp"
      ]
    },
    {
      "id": "cordova-plugin-splashscreen.SplashScreen",
      "file": "plugins/cordova-plugin-splashscreen/www/splashscreen.js",
      "pluginId": "cordova-plugin-splashscreen",
      "clobbers": [
        "navigator.splashscreen"
      ]
    },
    {
      "id": "cordova-plugin-fingerprint-aio.Fingerprint",
      "file": "plugins/cordova-plugin-fingerprint-aio/www/Fingerprint.js",
      "pluginId": "cordova-plugin-fingerprint-aio",
      "clobbers": [
        "Fingerprint"
      ]
    },
    {
      "id": "cordova-plugin-serial.Serial",
      "file": "plugins/cordova-plugin-serial/www/serial.js",
      "pluginId": "cordova-plugin-serial",
      "clobbers": [
        "window.serial"
      ]
    }
  ];
  module.exports.metadata = {
    "cordova-plugin-whitelist": "1.3.4",
    "cordova-plugin-chrome-apps-common": "1.0.7",
    "cordova-plugin-chrome-apps-sockets-udp": "1.3.0",
    "cordova-plugin-chrome-apps-sockets-tcp": "1.3.7",
    "cordova-plugin-splashscreen": "5.0.3",
    "cordova-plugin-fingerprint-aio": "3.0.1",
    "cordova-plugin-serial": "0.0.3"
  };
});
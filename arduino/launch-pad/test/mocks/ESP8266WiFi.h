#ifndef ESP8266WiFi_h
#define ESP8266WiFi_h

#include "IPAddress.h"
#include "WiFiServer.h"

typedef enum
{
	WL_NO_SHIELD = 255, // for compatibility with WiFi Shield library
	WL_IDLE_STATUS = 0,
	WL_NO_SSID_AVAIL = 1,
	WL_SCAN_COMPLETED = 2,
	WL_CONNECTED = 3,
	WL_CONNECT_FAILED = 4,
	WL_CONNECTION_LOST = 5,
	WL_DISCONNECTED = 6
} wl_status_t;

class WiFi_
{
	public:
		wl_status_t status();
		wl_status_t begin(char* ssid, char *passphrase);
};

extern WiFi_ WiFi;

#endif
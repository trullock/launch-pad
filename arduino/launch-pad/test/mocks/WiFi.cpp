#include "WiFi.h"

wl_status_t WiFi_::status()
{
	return WL_DISCONNECTED;
}

wl_status_t WiFi_::begin(char *ssid, char *passphrase)
{
	return WL_DISCONNECTED;
}

WiFi_ WiFi;
#include "WiFi.h"

wl_status_t WiFi_::status()
{
	return WL_DISCONNECTED;
}

wl_status_t WiFi_::begin(const char *ssid, const char *passphrase)
{
	return WL_DISCONNECTED;
}

WiFi_ WiFi;
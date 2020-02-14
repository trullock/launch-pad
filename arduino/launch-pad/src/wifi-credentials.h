#ifndef WifiCredentials_h
#define WifiCredentials_h

#define WifiCredentials_MaxSSIDLength 16
#define WifiCredentials_MaxPasswordLength 32

struct WifiCredentials
{
	const char* ssid;
	const char* password;
};

#endif
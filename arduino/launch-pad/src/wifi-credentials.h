#ifndef WifiCredentials_h
#define WifiCredentials_h

#define WifiCredentials_MaxSSIDLength 16
#define WifiCredentials_MaxPasswordLength 32

struct WifiCredentials
{
	char* ssid;
	char* password;
};

#endif
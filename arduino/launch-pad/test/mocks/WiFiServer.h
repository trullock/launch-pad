#ifndef WiFiServer_h
#define WiFiServer_h

#include "WiFiClient.h"

class WiFiServer
{
	//String readStringUntil(char end);
	public:
		WiFiServer(uint16_t port);
		void begin();
		WiFiClient available();
		bool hasClient();
};

#endif
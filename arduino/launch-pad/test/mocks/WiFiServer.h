#ifndef WiFiServer_h
#define WiFiServer_h

class WiFiServer
{
	//String readStringUntil(char end);
	public:
		WiFiServer(uint16_t port);
		bool available();
};

#endif
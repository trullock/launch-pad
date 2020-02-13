#ifndef WiFiClient_h
#define WiFiClient_h

class WiFiClient
{
	public:
		WiFiClient();
		bool available();
		bool connected();
		void stop();
		void keepAlive();
		int status();
		size_t readBytes(char *buffer, size_t length);
};

#endif
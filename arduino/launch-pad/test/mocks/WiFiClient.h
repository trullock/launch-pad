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
		void write(char data);
		void flush();
		size_t readBytes(char *buffer, size_t length);
};

#endif
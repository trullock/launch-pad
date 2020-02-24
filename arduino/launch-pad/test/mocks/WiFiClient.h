#ifndef WiFiClient_h
#define WiFiClient_h

class WiFiClient
{
	public:
		WiFiClient();
		bool available();
		bool connected();
		void stop();
		void keepAlive(int idle_sec, int interval_sec, int count);
		int status();
		void write(char* data);
		void flush();
		size_t readBytes(char *buffer, size_t length);

		static void setDefaultNoDelay(bool noDelay);
};

#endif
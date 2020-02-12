#ifndef WiFiUdp_h
#define WiFiUdp_h

#include "IPAddress.h"

class WiFiUDP 
{
	public:
		int beginPacket(IPAddress ip, uint16_t port);
		size_t write(const char *buffer, size_t size);
		int endPacket();
};

#endif
#include "WiFiClient.h"

WiFiClient::WiFiClient()
{

}

bool WiFiClient::available()
{
	return false;
}

bool WiFiClient::connected()
{
	return false;
}

void WiFiClient::stop()
{
}

void WiFiClient::keepAlive()
{
}

int WiFiClient::status()
{
	return 0;
}

size_t WiFiClient::readBytes(char *buffer, size_t length)
{
	return 0;
}

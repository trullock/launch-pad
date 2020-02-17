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

void WiFiClient::keepAlive(int idle_sec, int interval_sec, int count)
{
}

void WiFiClient::write(char data)
{
}

void WiFiClient::flush()
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

void WiFiClient::setDefaultNoDelay(bool noDelay)
{
}
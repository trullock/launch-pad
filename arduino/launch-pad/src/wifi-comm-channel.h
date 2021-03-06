#ifndef WifiCommChannel_h
#define WifiCommChannel_h

#include "ICommChannel.h"
#include "wifi-credentials.h"
#include "logger.h"
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

#define Wifi_State_Disconnected 0
#define Wifi_State_Connecting 1
#define Wifi_State_Connected 2

#define Wifi_Beacon_Interval_Millis 1000
#define Wifi_Connecting_TimeoutMillis 5000
#define Wifi_Tcp_Connection_TimeoutMillis 5000

class WifiCommChannel : public ICommChannel {
public:
	WifiCommChannel();
	~WifiCommChannel() {}
	void setConnectionDetails(WifiCredentials* creds);
	virtual char readCommand();
	virtual void writeStatus(char response, Status state);
	virtual bool isConnected();
	virtual void loop(unsigned long millis);
private:
	byte state;
	unsigned long lastEventMillis;
	unsigned long lastTcpEventMillis;
	bool tcpClientConnected = true;
	WifiCredentials* credentials;
	WiFiUDP udp;
	WiFiServer* tcp;
	WiFiClient tcpClient;
	IPAddress* broadcast;
	const char* beaconPacket = "LaunchPad:Hello";

	void connect(unsigned long millis);
	void disconnect();
	void beacon(unsigned long millis);
	char parseCommand(char *buffer);
	void checkForHello(unsigned long millis);
	bool checkTcpState(unsigned long millis);
};

#endif
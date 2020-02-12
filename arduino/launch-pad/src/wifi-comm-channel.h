#ifndef WifiCommChannel_h
#define WifiCommChannel_h

#include "ICommChannel.h"
#include "wifi-credentials.h"
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

#define Wifi_State_Disconnected 0
#define Wifi_State_Connecting 1
#define Wifi_State_Connected 2
#define Wifi_State_Beaconing 3
#define Wifi_State_TcpConnected 4

#define Wifi_Beacon_Interval_Millis 1000
#define Wifi_Connecting_TimeoutMillis 5000

class WifiCommChannel : public ICommChannel {
public:
	WifiCommChannel();
	~WifiCommChannel() {}
	void setConnectionDetails(WifiCredentials* creds);
	virtual char read();
	virtual void write(char data);
	virtual bool isConnected();
	virtual void loop(unsigned long millis);
private:
	byte state;
	unsigned long lastEventMillis;
	WifiCredentials* credentials;
	WiFiUDP udp;
	WiFiServer* tcp;
	IPAddress* broadcast;

	void connect(unsigned long millis);
	void disconnect();
	void beacon(unsigned long millis);
	void listenForTCP(unsigned long millis);
	void checkForHello(unsigned long millis);
};

#endif
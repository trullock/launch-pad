#include "wifi-comm-channel.h"


WifiCommChannel::WifiCommChannel()
{
	tcp = new WiFiServer(4321);
	
	u32_t b = 4294967295; // 255.255.255.255
	broadcast = new IPAddress(b);

	WifiCredentials creds;

	setConnectionDetails(&creds);
}

void WifiCommChannel::setConnectionDetails(WifiCredentials* creds)
{
	credentials = creds;
	//disconnect();
	//connect(0);
}

void WifiCommChannel::loop(unsigned long millis)
{
	switch(state)
	{
		case Wifi_State_Disconnected:
			Serial.println("Disconnected: connecting");
			connect(millis);
			break;

		case Wifi_State_Connecting:
			if(WiFi.status() == WL_CONNECTED)
			{
				Serial.println("Connecting: connected");
				state = Wifi_State_Connected;
				break;
			}

			if(millis >= lastEventMillis + Wifi_Connecting_TimeoutMillis)
			{
				Serial.println("Connecting: timeout disconnect");
				state = Wifi_State_Disconnected;
				// TODO: retry indefinitely, or abort at some point?
				break;
			}

		case Wifi_State_Connected:
			Serial.println("Connected: beaconing");
			state = Wifi_State_Beaconing;
			listenForTCP(millis);
			break;

		case Wifi_State_Beaconing:
			Serial.println("Beaconing: beaconing");
			beacon(millis);
			checkForHello(millis);
			break;
	}
}

void WifiCommChannel::beacon(unsigned long millis)
{
	if(millis >= lastEventMillis + Wifi_Beacon_Interval_Millis)
	{
		udp.beginPacket(*broadcast, 4321);
		char* buffer = "hello";
		udp.write(buffer, 5);
		udp.endPacket();

		lastEventMillis = millis;
	}
}

void WifiCommChannel::checkForHello(unsigned long millis)
{
	if(!tcp->available())
		return;

	// TODO: can we guarantee all of "HELLO\r\n" is available here? Should fit in one packet...

	//if(tcp.readStringUntil('\n') != String("HELLO"))
	//	return;

	state = Wifi_State_TcpConnected;
	lastEventMillis = millis;
	
}

void WifiCommChannel::connect(unsigned long millis)
{
	state = Wifi_State_Connecting;
	WiFi.begin(credentials->ssid, credentials->password);
	lastEventMillis = millis;
}

void WifiCommChannel::listenForTCP(unsigned long millis)
{
	tcp->begin();
	lastEventMillis = millis;
}

char WifiCommChannel::read()
{
	
}

void WifiCommChannel::write(char data)
{

}

bool WifiCommChannel::isConnected()
{
	return state == Wifi_State_TcpConnected;
}
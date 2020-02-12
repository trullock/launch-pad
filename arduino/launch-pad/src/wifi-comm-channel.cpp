#include "wifi-comm-channel.h"
#include "commands.h"

WifiCommChannel::WifiCommChannel()
{
	tcp = new WiFiServer(4321);
	broadcast = new IPAddress(255, 255, 255, 255);

	WifiCredentials creds;

	setConnectionDetails(&creds);

	lastEventMillis = 0;
	lastTcpEventMillis = 0;
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
				tcp->begin();
				lastEventMillis = millis;
				break;
			}

			if(millis >= lastEventMillis + Wifi_Connecting_TimeoutMillis)
			{
				Serial.println("Connecting: timeout disconnect");
				state = Wifi_State_Disconnected;
				lastEventMillis = millis;
				// TODO: retry indefinitely, or abort at some point?
				break;
			}
			break;

		case Wifi_State_Connected:
			checkTcpState(millis);
			beacon(millis);
			break;
	}
}

void WifiCommChannel::beacon(unsigned long millis)
{
	if(millis >= lastEventMillis + Wifi_Beacon_Interval_Millis)
	{
		Serial.println("Beaconing: actually beaconing");
		udp.beginPacket(*broadcast, 4321);
		udp.write(beaconPacket);
		udp.endPacket();
		udp.flush();

		lastEventMillis = millis;
	}
}

void WifiCommChannel::connect(unsigned long millis)
{
	state = Wifi_State_Connecting;
	WiFi.begin(credentials->ssid, credentials->password);
	lastEventMillis = millis;
}

char WifiCommChannel::parseCommand(char *buffer)
{
	if(strcmp("Arm", buffer) == 0)
		return Command_Arm;

	if (strcmp("Disarm", buffer) == 0)
		return Command_Disarm;

	if (strcmp("TestContinuity", buffer) == 0)
		return Command_TestContinuity;

	if (strcmp("Fire", buffer) == 0)
		return Command_Fire;

	return '\0';
}

bool WifiCommChannel::checkTcpState(unsigned long millis)
{
	if (tcp->hasClient())
	{
		// client waiting
		lastTcpEventMillis = millis;
		
		if (tcpClient.connected())
		{
			tcpClient.stop();
			// disconnected old client
		}
	}

	bool prevClientDisconnected = !tcpClient.connected();

	if (prevClientDisconnected)
		tcpClient = tcp->available();

	if (tcpClient.connected() && prevClientDisconnected)
	{
		if(prevClientDisconnected)
		{
			tcpClient.keepAlive();
			tcpClientConnected = true;
			lastTcpEventMillis = millis;

			// new connection
		} 
		else if(tcpClient.available())
		{
			// data waiting
			// this supports command and heartbeat timeout detection
			lastTcpEventMillis = millis;
		}
	}

	if (tcpClientConnected && tcpClient.status() == CLOSED)
	{
		// client has disconnected
		tcpClientConnected = false;
	}

	// check for application layer TCP timeout
	if (tcpClientConnected && lastTcpEventMillis + Wifi_Tcp_Connection_TimeoutMillis <= millis)
	{
		tcpClient.stop();
		tcpClientConnected = false;
	}

	return tcpClientConnected;
}

char WifiCommChannel::read()
{
	char command = '\0';

	if (tcpClient.connected() && tcpClient.available())
	{
		char buffer[16];
		for (int i = 0; i < 16; i++)
			buffer[i] = 0;

		tcpClient.readBytesUntil('\n', buffer, 16);
		
		command = parseCommand(buffer);
	}

	return command;
}

void WifiCommChannel::write(char data)
{

}

bool WifiCommChannel::isConnected()
{
	return tcpClient.connected();
}

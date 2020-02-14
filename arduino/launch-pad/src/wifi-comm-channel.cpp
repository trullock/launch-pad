#include "wifi-comm-channel.h"
#include "local-wifi-creds.h"
#include "commands.h"

WifiCommChannel::WifiCommChannel()
{
	tcp = new WiFiServer(4321);
	broadcast = new IPAddress(255, 255, 255, 255);

	WifiCredentials creds;
	creds.ssid = Wifi_SSID;
	creds.password = Wifi_Password;

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
			Log.println("WifiCommChannel::loop: Disconnected, connecting");
			connect(millis);
			break;

		case Wifi_State_Connecting:
			if(WiFi.status() == WL_CONNECTED)
			{
				Log.println("WifiCommChannel::loop: Connecting, connected");
				state = Wifi_State_Connected;
				tcp->begin();
				lastEventMillis = millis;
				break;
			}

			if(millis >= lastEventMillis + Wifi_Connecting_TimeoutMillis)
			{
				Log.println("WifiCommChannel::loop: Connecting, timeout, disconnecting");
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
		//Log.println("WifiCommChannel::beacon: Sending UDP beacon");
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
	Log.println(buffer);

	if(strcmp("Arm", buffer) == 0)
		return Command_Arm;

	if (strcmp("Disarm", buffer) == 0)
		return Command_Disarm;

	if (strcmp("TestContinuity", buffer) == 0)
		return Command_TestContinuity;

	if (strcmp("Fire", buffer) == 0)
		return Command_Fire;

	return Command_Null;
}

bool WifiCommChannel::checkTcpState(unsigned long millis)
{
	if (tcp->hasClient())
	{
		Log.println("WifiCommChannel::checkTcpState: New client waiting");
		// client waiting
		lastTcpEventMillis = millis;
		
		if (tcpClient.connected())
		{
			Log.println("WifiCommChannel::checkTcpState: Disconnecting old client");
			tcpClient.stop();
			// disconnected old client
		}
	}

	bool prevClientDisconnected = !tcpClient.connected();

	if (prevClientDisconnected)
		tcpClient = tcp->available();

	if (tcpClient.connected())
	{
		if(prevClientDisconnected)
		{
			tcpClient.keepAlive();
			tcpClientConnected = true;
			lastTcpEventMillis = millis;

			Log.println("WifiCommChannel::checkTcpState: New connection found");
			// new connection
		} 
		else if(tcpClient.available())
		{
			// data waiting
			// this supports command and heartbeat timeout detection
			lastTcpEventMillis = millis;

			Log.println("WifiCommChannel::checkTcpState: TCP data available");
		}
	}

	if (tcpClientConnected && tcpClient.status() == CLOSED)
	{
		// client has disconnected
		tcpClientConnected = false;

		Log.println("WifiCommChannel::checkTcpState: Client has disconnected");
	}

	// check for application layer TCP timeout
	if (tcpClientConnected && lastTcpEventMillis + Wifi_Tcp_Connection_TimeoutMillis <= millis)
	{
		tcpClient.stop();
		tcpClientConnected = false;

		Log.println("WifiCommChannel::checkTcpState: Application layer keepalive timeout");
	}

	return tcpClientConnected;
}

char WifiCommChannel::readCommand()
{
	char command = Command_Null;

	int availableBytes = tcpClient.available();

	if (tcpClient.connected() && availableBytes > 0)
	{
		Log.println("WifiCommChannel::read: Client is connected and data is available");
		Log.print("WifiCommChannel::read: available bytes: ");
		Log.println(availableBytes);

		char buffer[availableBytes];
		memset(buffer, 0x0, availableBytes);

		tcpClient.readBytes(buffer, availableBytes);
		command = parseCommand(buffer);

		Log.print("WifiCommChannel::read: Command received: ");
		Log.println(command);
	}

	return command;
}

void WifiCommChannel::writeResponse(char response)
{
	if(!isConnected())
		return;

	tcpClient.write(response);
	tcpClient.flush();
	yield();
}

bool WifiCommChannel::isConnected()
{
	return tcpClient.connected();
}

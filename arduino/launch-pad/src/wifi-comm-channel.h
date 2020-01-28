#ifndef UsbCommChannel_h
#define UsbCommChannel_h

#include "ICommChannel.h"

class WifiCommChannel : public ICommChannel {
  public:
	  WifiCommChannel();
	  ~WifiCommChannel() {}
	  
	  bool loop(unsigned long millis);
	  virtual char read();
	  virtual void write(char data);

	  int wifiStatus;
	  bool remoteConnected;
	  AltSoftSerial esp8266;
};

#endif
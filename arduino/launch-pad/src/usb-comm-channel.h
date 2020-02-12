#ifndef UsbCommChannel_h
#define UsbCommChannel_h

#include "ICommChannel.h"

class UsbCommChannel : public ICommChannel {
  public:
	  UsbCommChannel();
	  ~UsbCommChannel() {}
	  virtual void loop(unsigned long millis);
	  virtual char read();
	  virtual void write(char data);
	  virtual bool isConnected();
};

#endif
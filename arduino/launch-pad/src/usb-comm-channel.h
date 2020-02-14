#ifndef UsbCommChannel_h
#define UsbCommChannel_h

#include "ICommChannel.h"

class UsbCommChannel : public ICommChannel {
  public:
	  UsbCommChannel();
	  ~UsbCommChannel() {}
	  virtual void loop(unsigned long millis);
	  virtual char readCommand();
	  virtual void writeResponse(char response);
	  virtual bool isConnected();
};

#endif
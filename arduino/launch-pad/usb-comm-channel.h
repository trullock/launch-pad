#ifndef UsbCommChannel_h
#define UsbCommChannel_h

#include "ICommChannel.h"

class UsbCommChannel : public ICommChannel {
  public:
	  UsbCommChannel();
	  ~UsbCommChannel() {}
	  virtual char read();
	  virtual void write(char data);
};

#endif
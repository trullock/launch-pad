#ifndef ICommChannel_h
#define ICommChannel_h

#include "status.h"

class ICommChannel {
  public:
	virtual ~ICommChannel() {};
	virtual void loop(unsigned long millis) = 0;
	virtual char readCommand() = 0;
	virtual void writeStatus(char response, Status state) = 0;
	virtual bool isConnected() = 0;
};

#endif
#ifndef ICommChannel_h
#define ICommChannel_h


class ICommChannel {
  public:
	virtual ~ICommChannel() {};
	virtual void loop(unsigned long millis) = 0;
	virtual char read() = 0;
	virtual void write(char data) = 0;
	virtual bool isConnected() = 0;
};

#endif
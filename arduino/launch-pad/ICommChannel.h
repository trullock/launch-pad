#ifndef ICommChannel_h
#define ICommChannel_h


class ICommChannel {
  public:
	virtual ~ICommChannel() {};
	virtual char read() = 0;
	virtual void write(char data) = 0;
};

#endif
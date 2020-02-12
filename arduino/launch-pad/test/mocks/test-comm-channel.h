#include "../../src/ICommChannel.h"

class TestCommChannel : public ICommChannel
{
public:
	TestCommChannel();
	~TestCommChannel() {};
	char read();
	void pushReadChar(char c);
	void write(char data);
	char getWrittenChar();
	char getLastChar();
	void reset();
	void setConnected(bool c);
	bool isConnected();
	
private:
	char readBuffer[16];
	int readReadIndex = 0;
	int readWriteIndex = 0;

	char writeBuffer[16];
	int writeWriteIndex = 0;
	int writeReadIndex = 0;

	bool connected;
};
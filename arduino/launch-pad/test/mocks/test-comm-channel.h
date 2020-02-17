#include "../../src/ICommChannel.h"

class TestCommChannel : public ICommChannel
{
public:
	TestCommChannel();
	~TestCommChannel() {};
	char readCommand();
	void pushReadChar(char c);
	void writeResponse(char response);
	void writeStatus(char response, Status state);
	char getWrittenChar();
	char getLastChar();
	void reset();
	void setConnected(bool c);
	bool isConnected();
	void loop(unsigned long millis);
	
private:
	char readBuffer[16];
	int readReadIndex = 0;
	int readWriteIndex = 0;

	char writeBuffer[16];
	int writeWriteIndex = 0;
	int writeReadIndex = 0;

	bool connected;
};
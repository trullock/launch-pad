#ifndef Serial_h
#define Serial_h

#include <WString.h>

class Serial_
{
public:
	Serial_();
    void begin(unsigned long);
    int available(void);
    int read(void);

	void pushData(int);
	void reset();
	void println(char c);
	void println(const char c[]);
	void println(String s);
	void println(String* s);
	void print(const char c[]);
	void print(char c);

private:
	int buffer[16];
	int bufferIndex;
	int bufferSize;
};

extern Serial_ Serial;

#endif
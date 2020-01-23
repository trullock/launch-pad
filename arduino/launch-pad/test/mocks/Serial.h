#ifndef Serial_h
#define Serial_h

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

private:
	int buffer[16];
	int bufferIndex;
	int bufferSize;
};

extern Serial_ Serial;

#endif
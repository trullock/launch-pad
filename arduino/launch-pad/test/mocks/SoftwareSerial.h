#ifndef SoftwareSerial_h
#define SoftwareSerial_h

class SoftwareSerial
{

public:
	SoftwareSerial(uint8_t receivePin, uint8_t transmitPin);
	void begin(long speed);
	void write(uint8_t byte);
	char read();
	int available();

	void print(String s);
	void println(String s);

	void print(const unsigned char c);
	void print(const char str[]);
	void println(uint32_t i);
	void println(const char str[]);
	char *readStringUntil(const char c);

	void println(void);
	void println(const String &s);

	String readString();
};

#endif

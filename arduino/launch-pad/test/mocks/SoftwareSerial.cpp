#include "SoftwareSerial.h"

SoftwareSerial::SoftwareSerial(byte receivePin, byte transmitPin)
{
}
void SoftwareSerial::begin(long speed)
{
}
void SoftwareSerial::write(byte byte)
{
}
char SoftwareSerial::read()
{
	return 0;
}
int SoftwareSerial::available()
{
	return 0;
}

void SoftwareSerial::print(String s) { }
void SoftwareSerial::println(String s) { }

void SoftwareSerial::print(const unsigned char c) {}
void SoftwareSerial::print(const char str[]) {}
void SoftwareSerial::println(uint32_t i) {}
void SoftwareSerial::println(const char str[]) {}
char* SoftwareSerial::readStringUntil(const char c)
{
	return "";
}

void SoftwareSerial::println(void) {}
void SoftwareSerial::println(const String &s) { }

String SoftwareSerial::readString() {
	return "";
}
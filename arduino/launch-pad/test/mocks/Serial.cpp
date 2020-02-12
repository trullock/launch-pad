#include "Serial.h"

Serial_::Serial_() {
	reset();
}

void Serial_::begin(unsigned long)
{
}

int Serial_::available(void)
{
    return bufferIndex < bufferSize;
}

int Serial_::read(void)
{
    int value = buffer[bufferIndex];
	bufferIndex++;
	return value;
}

void Serial_::pushData(int data){
	buffer[bufferSize] = data;
	bufferSize++;
}

void Serial_::println(char c) { }
void Serial_::println(const char c[]) {}
void Serial_::println(String s) {}
void Serial_::println(String *s) {}
void Serial_::print(const char c[]) {}

void Serial_::reset()
{
	bufferIndex = 0;
	bufferSize = 0;

	for (int i = 0; i < 16; i++)
		buffer[i] = 0;
}

Serial_ Serial;
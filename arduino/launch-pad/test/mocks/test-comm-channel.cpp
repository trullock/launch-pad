#include "test-comm-channel.h"

TestCommChannel::TestCommChannel()
{
	reset();
}

void TestCommChannel::reset() 
{
	for (int i = 0; i < 16; i++)
	{
		readBuffer[i] = 0;
		writeBuffer[i] = 0;
	}

	readReadIndex = 0;
	readWriteIndex = 0;
	writeReadIndex = 0;
	writeWriteIndex = 0;
}

char TestCommChannel::read()
{
	return readBuffer[readReadIndex++];
}

void TestCommChannel::pushReadChar(char c)
{
	readBuffer[readWriteIndex++] = c;
}

void TestCommChannel::write(char data)
{
	writeBuffer[writeWriteIndex++] = data;
}

char TestCommChannel::getWrittenChar()
{
	return writeBuffer[writeReadIndex++];
}
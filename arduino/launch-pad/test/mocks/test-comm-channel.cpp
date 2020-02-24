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

	connected = false;
}

char TestCommChannel::readCommand()
{
	return readBuffer[readReadIndex++];
}

void TestCommChannel::pushReadChar(char c)
{
	readBuffer[readWriteIndex++] = c;
}

void TestCommChannel::writeResponse(char response)
{
	writeBuffer[writeWriteIndex++] = response;
}

void TestCommChannel::writeStatus(char response, Status state)
{
	writeResponse(response);
	writeResponse(state.state);
	writeResponse(state.interlockEngaged ? 1 : 0);
}

char TestCommChannel::getWrittenChar()
{
	return writeBuffer[writeReadIndex++];
}

char TestCommChannel::getLastChar()
{
	return writeBuffer[readWriteIndex];
}

bool TestCommChannel::isConnected()
{
	return connected;
}

void TestCommChannel::setConnected(bool c)
{
	connected = c;
}

void TestCommChannel::loop(unsigned long millis)
{
	
}
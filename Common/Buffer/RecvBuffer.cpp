#include "pch.h"
#include "RecvBuffer.h"

RecvBuffer::RecvBuffer(UInt32 _bufSize)
 : bufferSize (_bufSize)
{
	capacity = bufferSize * bufferCount;
	buffer.resize(capacity);
}

RecvBuffer::~RecvBuffer()
{
}

void RecvBuffer::Clean()
{
	if(readPos == writePos) {
		readPos = writePos = 0;
	}
	else {
		if(FreeSize() < bufferSize) {
			memcpy_s(&buffer[0], DataSize(), &buffer[readPos], DataSize());
			readPos = 0;
			writePos = DataSize();
		}
	}
}

bool RecvBuffer::OnRead(UInt32 _bytes)
{
	if(_bytes > DataSize()) {
		return false;
	}
	readPos += _bytes;
	return true;
}

bool RecvBuffer::OnWrite(UInt32 _bytes)
{
	if(_bytes > FreeSize()) {
		return false;
	}
	writePos += _bytes;
	return true;
}

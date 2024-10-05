#include "pch.h"
#include "SendBuffer.h"

SendBuffer::SendBuffer(UInt32 _bufSize)
{
	buffer.resize(_bufSize);
}

SendBuffer::~SendBuffer()
{
	buffer.clear();
}

void SendBuffer::CopyData(BYTE* _buf, UInt32 _len)
{
	ASSERT_CRASH(Capacity() >= _len);

	memcpy_s(buffer.data(), _len, _buf, _len);
	writeSize = _len;
}

#include "pch.h"
#include "Lock.h"
#include "PacketBuffer.h"

void PacketBuffer::Calc()
{
	BYTE* headPtr = header;
	memcpy_s(headPtr, HeaderSize(), &writePos, sizeof(UInt32));
}

void PacketBuffer::Render()
{
	printf("Header : %d\n", *header);
	printf("write Pos : %d\n", writePos);
	printf("Body : %s\n", reinterpret_cast<const char*>(body));
	printf("================\n");
}

void PacketBuffer::WriteBytes(BYTE* _start, UInt32 _size)
{
	ASSERT_CRASH(writePos + _size < BODY_BUF_SIZE);
	memcpy_s(body+writePos, _size, _start, _size);
	writePos += _size;
	return ;
}

void PacketBuffer::ReadBytes(BYTE* _start, UInt32 _size)
{
	ASSERT_CRASH(readPos < BODY_BUF_SIZE);
	memcpy_s(_start, _size, body+readPos, _size);
	readPos += _size;
	return ;
}

void PacketBuffer::OnWrite(UInt32 _len)
{
	ASSERT_CRASH(writePos + _len <= BODY_BUF_SIZE);
	writePos += _len;
}

void PacketBuffer::OnRead(UInt32 _len)
{
	ASSERT_CRASH(readPos + _len <= BODY_BUF_SIZE);
	readPos += _len;
}

void PacketBuffer::ClearHeader()
{
	ZeroMemory(header, HEADER_BUF_SIZE);
}

void PacketBuffer::ClearBody()
{
	ZeroMemory(body, BODY_BUF_SIZE);
	writePos = 0;
}

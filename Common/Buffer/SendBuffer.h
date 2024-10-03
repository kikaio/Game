#pragma once

class SendBuffer
{
public:
	SendBuffer(UInt32 _bufSize);
	~SendBuffer();
private:
	vector<BYTE> buffer;
	UInt32 writeSize = 0;
public:
	BYTE* Buffer() { return buffer.data(); }
	UInt32 WriteSize() { return writeSize; }
	UInt64 Capacity() { return buffer.size(); }

	void CopyData(BYTE* _buf, UInt32 _len);
};

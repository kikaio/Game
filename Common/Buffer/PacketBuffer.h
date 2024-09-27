#pragma once

class PacketBuffer
{
private:
	BYTE header[HEADER_BUF_SIZE] = {0, };
	BYTE body[BODY_BUF_SIZE] = {0, };
private:
	UInt32 writePos = 0;
	UInt32 readPos = 0;
public:
	void Calc();
	

	UInt32 HeaderSize() {
		return HEADER_BUF_SIZE;
	}

	UInt32 BodySize() {
		return BODY_BUF_SIZE;
	}
	void Render();
	
	void WriteBytes(BYTE* _start, UInt32 _size);
	void ReadBytes(BYTE* _start, UInt32 _size);
	void ClearHeader();
	void ClearBody();
	BYTE* GetHeaderPtr() {
		return header;
	}

	BYTE* GetBodyPtr(UInt32 _delta = 0) {
		return body + _delta;
	}

	UInt32 GetWritableSize() {
		return BODY_BUF_SIZE - writePos;
	}
};

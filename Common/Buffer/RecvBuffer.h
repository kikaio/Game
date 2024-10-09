#pragma once

class RecvBuffer
{
	const UInt32 bufferCount = 10;
public:
	RecvBuffer(UInt32 _bufSize);
	~RecvBuffer();
private:
	UInt32 capacity;
	UInt32 bufferSize = 0;
	UInt32 readPos = 0;
	UInt32 writePos = 0;
	vector<BYTE> buffer;
public:
	void Clean();
	bool OnRead(UInt32 _bytes);
	bool OnWrite(UInt32 _bytes);

	BYTE* ReadPos() {
		return &buffer[readPos];
	}

	BYTE* WritePos() {
		return &buffer[writePos];
	}

	UInt32 DataSize() {
		ASSERT_CRASH(readPos < writePos);
		if(readPos > writePos) {
			//todo ASSERT ?
			printf("read pos must less than write pos\n");
			return 0;
		}
		return writePos - readPos;
	}

	UInt32 FreeSize() {
		return capacity - writePos;
	}

	void Render() {
		printf("RecvBuffer\n");
		for(uint32_t _idx = readPos; _idx < writePos; _idx++) {
			printf("%c-", buffer[_idx]);
		}
		printf("\n");
	}
};

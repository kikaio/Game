#pragma once

class SendBuffer : public enable_shared_from_this<SendBuffer>
{
public:
	SendBuffer(SendBufferChunkSptr _owner, BYTE* _buffer, int32_t _allocSize);
	~SendBuffer();
private:
	BYTE*  buffer = nullptr;
	UInt32 writeSize = 0;
	UInt32 allocSize = 0;
	SendBufferChunkSptr owner = nullptr;
public:
	BYTE* Buffer() { return buffer; }
	UInt32 WriteSize() { return writeSize; }
	void Close(uint32_t _writeSize);
};


class SendBufferChunk : public enable_shared_from_this<SendBufferChunk>
{
	enum {
		SEND_BUFFER_CHUNK_SIZE = BUF_4096 //0x1000과 같은 값. => 16^3
	};
public:
	SendBufferChunk();
	~SendBufferChunk();
private:
	Array<BYTE, SEND_BUFFER_CHUNK_SIZE> buffer = {};
 	bool open = false;
	uint32_t usedSize = 0;
public:
	void Reset();
	SendBufferSptr Open(uint32_t _allocSize);
	void Close(uint32_t _writeSize);

	bool IsOpen() {
		return open;
	}

	//chunk에서 미사용중인 부분의 ptr을 반환.
	BYTE* Buffer() {
		return &buffer[usedSize];
	}

	uint32_t FreeSize() {
		return static_cast<uint32_t>(buffer.size() - usedSize);
	}
};


class SendBufferManager : public Singleton<SendBufferManager>
{
public:
private:
	VAL_LOCK(chunkLock);
	Vector<SendBufferChunkSptr> sendBufferChunks;
private:
	SendBufferChunkSptr Pop();
	void Push(SendBufferChunkSptr _buffer);

	static void PushGlobal(SendBufferChunk* _chunk);
public:
	SendBufferSptr Open(uint32_t _size);

};
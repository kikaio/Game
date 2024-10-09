#include "pch.h"
#include "SendBuffer.h"

SendBuffer::SendBuffer(SendBufferChunkSptr _owner, BYTE* _buffer, int32_t _allocSize)
 : owner(_owner), buffer(_buffer), allocSize(_allocSize)
{
}

SendBuffer::~SendBuffer()
{
}

void SendBuffer::Close(uint32_t _writeSize)
{
	ASSERT_CRASH(allocSize >= _writeSize);
	writeSize = _writeSize;
	owner->Close(writeSize);
}


SendBufferChunk::SendBufferChunk()
{
}

SendBufferChunk::~SendBufferChunk()
{
}

void SendBufferChunk::Reset()
{
	open = false;
	usedSize = 0;
}

//해당 allocSize 만큼 할당해서 넘긴다는 개념
SendBufferSptr SendBufferChunk::Open(uint32_t _allocSize)
{
	ASSERT_CRASH(_allocSize <= SEND_BUFFER_CHUNK_SIZE);
	ASSERT_CRASH(open == false);

	if(_allocSize > FreeSize()) {
		return nullptr;
	}
	open = true;
	return make_shared<SendBuffer>(shared_from_this(), Buffer(), _allocSize);
//	return MakeShared<SendBuffer>(shared_from_this(), Buffer(), _allocSize);
}

void SendBufferChunk::Close(uint32_t _writeSize)
{
	ASSERT_CRASH(open == true);
	open = false;
	usedSize += _writeSize;
}


SendBufferChunkSptr SendBufferManager::Pop()
{
	{
		LOCK_GUARDDING(chunkLock);
		if (sendBufferChunks.empty() == false) {
			SendBufferChunkSptr sptr = sendBufferChunks.back();
			sendBufferChunks.pop_back();
			return sptr;
		}
	}
	return SendBufferChunkSptr(xnew<SendBufferChunk>(), PushGlobal);
}

void SendBufferManager::Push(SendBufferChunkSptr _buffer)
{
	LOCK_GUARDDING(chunkLock);
	sendBufferChunks.push_back(_buffer);
}

void SendBufferManager::PushGlobal(SendBufferChunk* _chunk)
{
	SendBufferManager::Get().Push(SendBufferChunkSptr(_chunk, PushGlobal));
}

// buffer에서 특정 부분을 반환.
SendBufferSptr SendBufferManager::Open(uint32_t _size)
{
	if(LSendBufferChunk == nullptr) {
		LSendBufferChunk = Pop();
		LSendBufferChunk->Reset();
	}
	//chunk의 중복 open 방지.
	ASSERT_CRASH(LSendBufferChunk->IsOpen() == false);
	if(LSendBufferChunk->FreeSize() < _size) {
		//이전에 할당 된 chunk는 참조가 0이될 때 알아서 sendBufferChunks로 반환된다.
		LSendBufferChunk = Pop();
		LSendBufferChunk->Reset();
	}
	return LSendBufferChunk->Open(_size);
}

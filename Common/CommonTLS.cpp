#include "pch.h"
#include "CommonTLS.h"

thread_local ThreadId LThreadId;
thread_local int64_t LEndTickCount = 0;

//thread_local std::stack<LockId> LLockStack;
thread_local std::vector<LockId> LLockStack;
thread_local SendBufferChunkSptr LSendBufferChunk = nullptr;
thread_local JobQueue* LCurrentJobQueue = nullptr;
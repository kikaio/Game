#pragma once

extern thread_local UInt32 LThreadId;
extern thread_local int64_t LEndTickCount;

//extern thread_local std::stack<LockId> LLockStack;
extern thread_local std::vector<LockId> LLockStack;
extern thread_local SendBufferChunkSptr LSendBufferChunk;

extern thread_local class JobQueue* LCurrentJobQueue;
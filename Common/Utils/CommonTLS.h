#pragma once

extern thread_local UInt32 LThreadId;

//extern thread_local std::stack<LockId> LLockStack;
extern thread_local std::vector<LockId> LLockStack;

#include "pch.h"
#include "CommonTLS.h"

thread_local ThreadId LThreadId;

//thread_local std::stack<LockId> LLockStack;
thread_local std::vector<LockId> LLockStack;

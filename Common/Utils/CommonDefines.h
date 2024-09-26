
//단순 define 들.
#ifndef OUT
#define OUT
#endif

#ifndef IN
#define IN
#endif


#define VAL_LOCK(lockName)								Lock lockName = (#lockName)
#define LOCK_GUARDDING(_targetObj)						LockGuard guardFor##_targetObj(_targetObj, __FILE__, __LINE__)

#define VAL_RW_LOCK(lockName)							ReadWriteLock lockName = (#lockName)


#define USE_STOMP_ALLOC false
#if USE_STOMP_ALLOC
#define XALLOC(size)					StompAllocator::Alloc(size)
#define XRELEASE(ptr)					StompAllocator::Release(ptr)
#else
#if true
#define XALLOC(size)					Memory::Get().Alloc(size)
#define XRELEASE(ptr)					Memory::Get().Release(ptr)
#else
#define XALLOC(size)					BaseAllocator::Alloc(size)
#define XRELEASE(ptr)					BaseAllocator::Release(ptr)
#endif
#endif


#define LOCK_MGR()			LockManager::Get()
#define MEM_MGR()			Memory::Get()
#define INVALID_LINE_NO		-1;

#define DO_LOCK_TRACKING_LOG			false
#define EMPTY_CONST_CHAR				""



#define HEADER_BUF_SIZE 32
#define BODY_BUF_SIZE 256
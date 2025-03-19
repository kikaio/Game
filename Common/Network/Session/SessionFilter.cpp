#include "pch.h"
#include "SessionFilter.h"

void SessionFilter::SetFilter(SESSION_FILTER _filter)
{
	sessionFilter = _filter;
}

bool SessionFilter::Encrypt(BYTE* _buf, int32_t _size, string _key)
{
	return true;
}

bool SessionFilter::Decrypt(BYTE* _buf, int32_t _size, string _key)
{
	return true;
}

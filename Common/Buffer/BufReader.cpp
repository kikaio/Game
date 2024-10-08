#include "pch.h"
#include "BufReader.h"

bool BufReader::Peek(void* _dest, uint32_t _len)
{
	if(FreeSize() < _len) {
		return false;
	}
	memcpy(_dest, &buf[pos], _len);
	return true;
}

bool BufReader::Read(void* _dest, uint32_t _len)
{
	if(Peek(_dest, _len) == false) {
		return false;
	}
	pos += _len;	
	return true;
}

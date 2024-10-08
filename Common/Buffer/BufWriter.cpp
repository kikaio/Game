#include "pch.h"
#include "Lock.h"
#include "BufWriter.h"

bool BufWriter::Write(void* _src, uint32_t _len)
{
	if(FreeSize() < _len) {
		return false;
	}
	memcpy(&buf[pos], _src, _len);
	pos += _len;
	return true;
}

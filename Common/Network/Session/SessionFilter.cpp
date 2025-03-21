#include "pch.h"
#include "SessionFilter.h"

#include <Krypt/Krypt.hpp>

bool SessionFilter::EncryptXor(BYTE* _buf, int32_t _size, const string& _key)
{
	if (_key.length() == 0) {
		return false;
	}
	int keyIdx = 0;
	for (int idx = 0; idx < _size; idx++) {
		BYTE* _c = _buf + idx;
		*_c = *_c ^ _key[keyIdx++];
		keyIdx %= _key.size();
	}
	return true;
}

bool SessionFilter::DecryptXor(BYTE* _buf, int32_t _size, const string& _key)
{
	if (_key.length() == 0) {
		return false;
	}
	int keyIdx = 0;
	for (int idx = 0; idx < _size; idx++) {
		BYTE* _c = _buf + idx;
		*_c = *_c ^ _key[keyIdx++];
		keyIdx %= _key.size();
	}
	return true;
}

void SessionFilter::SetFilter(SESSION_FILTER _filter)
{
	sessionFilter = _filter;
}

bool SessionFilter::Encrypt(BYTE* _buf, int32_t _size, const string& _key)
{
	switch (sessionFilter) {
	case SESSION_FILTER::XOR: {
		return EncryptXor(_buf, _size, _key);
	}
	default: {
		return true;
	}
	}
}

bool SessionFilter::Decrypt(BYTE* _buf, int32_t _size, const string& _key)
{
	switch (sessionFilter) {
	case SESSION_FILTER::XOR: {
		return DecryptXor(_buf, _size, _key);
	}
	default: {
		return true;
	}
	}
}

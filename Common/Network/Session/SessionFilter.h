#pragma once

class SessionFilter
{
private:
	SESSION_FILTER sessionFilter = SESSION_FILTER::NONE;
private:
	bool EncryptXor(BYTE* _buf, int32_t _size, const string& _key);
	bool DecryptXor(BYTE* _buf, int32_t _size, const string& _key);
public:
	void SetFilter(SESSION_FILTER _filter);
public:
	bool Encrypt(BYTE* _buf, int32_t _size, const string& _key);
	bool Decrypt(BYTE* _buf, int32_t _size, const string& _key);
};

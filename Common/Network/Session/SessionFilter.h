#pragma once

class SessionFilter : public TLSSingleton<SessionFilter>
{
private:
	SESSION_FILTER sessionFilter = SESSION_FILTER::NONE;
public:
	void SetFilter(SESSION_FILTER _filter);
public:
	bool Encrypt(BYTE* _buf, int32_t _size, string _key);
	bool Decrypt(BYTE* _buf, int32_t _size, string _key);
};

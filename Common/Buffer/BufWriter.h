#pragma once

#include "PacketBuffer.h"

class BufWriter
{
	friend class PacketBuffer;
public:

	BufWriter(PacketBuffer& _buf) : buf(_buf) {
	}
	~BufWriter() = default;
private:
	PacketBuffer& buf;
public:
	template<typename T>
	BufWriter& operator<<(T& _val) {
		buf.WriteBytes(reinterpret_cast<BYTE*>(&_val), sizeof(T));
		return *this;
	}

	BufWriter& operator<< (string _str) {
		size_t len = _str.size();
		buf.WriteBytes(reinterpret_cast<BYTE*>(&len), sizeof(len));
		for (char _ch : _str) {
			buf.WriteBytes(reinterpret_cast<BYTE*>(&_ch), sizeof(_ch));
		}
		return *this;
	}

};
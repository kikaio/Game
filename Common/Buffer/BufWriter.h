#pragma once

#include "PacketBuffer.h"


class BufWriter
{
public:

	BufWriter() {
	}

	BufWriter(BYTE* _buf, uint32_t _size, uint32_t _pos = 0)
		: buf(_buf), size(_size), pos(_pos) {
	}
	~BufWriter() {
	}
private:
	BYTE* buf = nullptr;
	uint32_t size = 0;
	uint32_t pos = 0;
public:
	BYTE* Buffer() { return buf; }
	uint32_t Size() { return size; }
	uint32_t WriteSize() { return pos; }
	uint32_t FreeSize() { return size - pos; }
public:
	template<typename T> 
	T* Reserve();

	template<typename T>
	bool Write(T* _src) { return Write(_src, sizeof(T)); }
	bool Write(void* _src, uint32_t _len);
	bool Write(string& _str) {
		bool ret = true;
		uint32_t len = _str.size();
		operator<<(len);

		for(uint32_t idx = 0; idx < _str.size(); idx++) {
			operator<<(_str[idx]);
		}
		return true;
	}



public:
	template<typename T>
	BufWriter& operator<<(OUT const T& _src);
	template<typename T>
	BufWriter& operator<<(OUT T&& _src);

};


template<typename T>
T* BufWriter::Reserve()
{
	if(FreeSize() < sizeof(T)) {
		return nullptr;
	}
	T* ret = reinterpret_cast<T*>(&buf[pos]);
	pos += sizeof(T);
	return ret;
}


template<typename T>
BufWriter& BufWriter::operator<<(const T& _src) {
	*(reinterpret_cast<T*>(&buf[pos])) = _src;
	pos += sizeof(T);
	return *this;
}

template<typename T>
BufWriter& BufWriter::operator<<(T&& _src) {
	using DataType = std::remove_reference_t<T>;
	*(reinterpret_cast<DataType*>(&buf[pos])) = std::forward<DataType>(_src);
	pos += sizeof(T);
	return *this;
}

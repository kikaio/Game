#pragma once

class BufReader
{
public:

	BufReader() {
	}

	BufReader(BYTE* _buf, uint32_t _size, uint32_t _pos = 0)
		: buf(_buf), size(_size), pos(_pos) {
	}
	~BufReader() {
	}
private:
	BYTE* buf = nullptr;
	uint32_t size = 0;
	uint32_t pos = 0;
public:
	BYTE* Buffer() { return buf;}
	uint32_t Size() { return size;}
	uint32_t ReadSize() { return pos; }
	uint32_t FreeSize() { return size-pos; }
	template<typename T> 
	bool Peek(T* _dest) { return Peek(_dest, sizeof(T)); }
	bool Peek(void* _dest, uint32_t _len);

	template<typename T> 
	bool Read(T* _dest) { return Read(_dest, sizeof(T)); }
	bool Read(void* _dest, uint32_t _len);

	bool Read(string& _val) {
		uint32_t len = 0;
		operator >> (len);
		_val.resize(len, '\0');
		for(uint32_t idx = 0; idx < len; idx++) {
			operator>>(_val[idx]);
		}
		return true;
	}

	template<typename T>
	BufReader& operator>>(OUT T& _inputVal);
		
	void Render() {
		printf("bufreader\n");
		for(uint32_t idx = pos; idx < size; ++idx) {
			printf("%c, ", buf[idx]);
		}
		printf("\n");
	}
};


template<typename T>
BufReader& BufReader::operator>>(OUT T& _dest) {
	auto dest = reinterpret_cast<void*>(&_dest);
	memcpy(dest, &buf[pos], sizeof(T));
	pos += sizeof(T);
	return *this;
}
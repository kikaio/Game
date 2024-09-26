#pragma once

class BufReader
{
	friend class PacketBuffer;
public:
	BufReader(PacketBuffer& _buf) : buf(_buf) {
	}
private:
	PacketBuffer& buf;
public:

	template<typename T>
	BufReader& operator>>(OUT T& _inputVal) {
		buf.ReadBytes(reinterpret_cast<BYTE*>(&_inputVal), sizeof(T));
		return *this;
	}

	BufReader& operator>>(OUT string& _val) {
		UInt16 strLen = 0;
		buf.ReadBytes(reinterpret_cast<BYTE*>(&strLen), sizeof(strLen));
		for (int idx = 0; idx < strLen; idx++) {
			char ch = '\0';
			buf.ReadBytes(reinterpret_cast<BYTE*>(&ch), sizeof(ch));
			_val.push_back(ch);
		}
		return *this;
	}

};


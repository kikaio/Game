#pragma once


template <int32_t C>
struct FullBits {
	enum {
		value = (1 << (C-1)) | FullBits<C-1>::value
	};
};

template<>
struct FullBits<1> {
	enum {
		value = 1
	};
};

template<>
struct FullBits<0> {
	enum {
		value = 0
	};
};


template<int32_t paramCnt, int32_t columnCnt>
class DBBind
{
public:
	DBBind(DBConnection& _conn, const char* _query) 
	 : conn(_conn), query(_query)
	{
		::memset(paramIdx, 0, sizeof(paramIdx));
		::memset(columnIdx, 0, sizeof(columnIdx));
		paramFlag = 0;
		columnFlag = 0;
		conn.Unbind();
	}
protected:
	DBConnection& conn;
	const char* query;
	SQLLEN paramIdx[paramCnt > 0 ? paramCnt : 1] = {0, };
	SQLLEN columnIdx[columnCnt > 0 ? columnCnt : 1] = { 0, };
	uint64_t paramFlag = 0;
	uint64_t columnFlag = 0;
public:
	bool Validate() {
		auto paramVal = FullBits<paramCnt>::value;
		auto columnVal = FullBits<columnCnt>::value;
		return (paramFlag == paramVal) && (columnFlag == columnVal);
	}

	bool Execute() {
		ASSERT_CRASH(Validate());
		return conn.Execute(query);
	}

	bool Fetch() {
		return conn.Fetch();
	}
public:
	void BindParam(int32_t _idx, int32_t _val) {
		conn.BindParam(_idx + 1, &_val, &paramIdx[_idx]);
		paramFlag |= (1LL << _idx);
	}
	
	template<typename T>
	void BindParam(int32_t _idx, T& _val) {
		conn.BindParam(_idx+1, &_val, &paramIdx[_idx]);
		paramFlag |= (1LL << _idx);
	}

	void BindParam(int32_t _idx, const char* _val) {
		conn.BindParam(_idx+1, _val, &paramIdx[_idx]);
		paramFlag |= (1LL << _idx);
	}

	template<typename T, int32_t N>
	void BindParam(int32_t _idx, T(&_val)[N]) {
		conn.BindParam(_idx + 1, (const BYTE*)_val, sizeof(T) * N, &paramIdx[_idx]);
		paramFlag |= (1LL << _idx);
	}

	template<typename T>
	void BindParam(int32_t _idx, T* _val, int32_t N) {
		conn.BindParam(_idx + 1, (const BYTE*)_val, sizeof(T) * N, &paramIdx[_idx]);
		paramFlag |= (1LL << _idx);
	}

	void BindCol(int32_t _idx, string& _val) {
		conn.BindCol(_idx + 1, const_cast<char*>(_val.c_str()), _val.size(), &columnIdx[_idx]);
		columnFlag |= (1LL << _idx);
	}

	template <typename T>
	void BindCol(int32_t _idx, T& _val) {
		conn.BindCol(_idx+1, &_val, &columnIdx[_idx]);
		columnFlag |= (1LL << _idx);
	}

	template<int32_t N>
	void BindCol(int32_t _idx, char(&_val)[N]) {
		conn.BindCol(_idx+1, _val, N-1, &columnIdx[_idx]);
		columnFlag |= (1LL << _idx);
	}

	
	void BindCol(int32_t _idx, char* _val, int32_t _len) {
		conn.BindCol(_idx + 1, _val, _len - 1, &columnIdx[_idx]);
		columnFlag |= (1LL << _idx);
	}

	template<typename T, int32_t N> 
	void BindCol(int32_t _idx, T(&_val)[N]) {
		conn.BindCol(_idx+1, _val, sizeof(T) * N, &columnIdx[_idx]);
		columnFlag |= (1LL <<  _idx);
	}


};
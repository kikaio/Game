#pragma once


class DBConnection
{
private:
	DBNameType dbNameType = DBNameType::NONE;
	RWType rwType = RWType::NONE;
public:
	DBNameType DbNameType() {
		return dbNameType;
	}
	RWType RwType() {
		return rwType;
	}
private:
	SQLHDBC hdbc = SQL_NULL_HANDLE;
	SQLHSTMT statement = SQL_NULL_HANDLE;
private:
	bool BindParam(SQLUSMALLINT _paramIdx, SQLSMALLINT _cType, SQLSMALLINT _sqlType
		, SQLULEN _len, SQLPOINTER _ptr, SQLLEN* _idx
	);
	bool BindCol(SQLUSMALLINT _conIdx, SQLSMALLINT _cType, SQLULEN len, SQLPOINTER _val, SQLLEN* _idx);
	void HandleError(SQLRETURN _ret);
public:
	bool Connect(SQLHENV _henv, const char* _connStr);
	bool Connect(SQLHENV _henv, string _odbcName, string _host, string _user, string _pwd, DBNameType _dbNameType, RWType _rwType);
	void Clear();
	bool Execute(const char* _sql);
	bool Fetch();
	bool HasNext();
	int32_t GetRowCount();
	void Unbind();
public:
	bool BindParam(int32_t _idx, bool* _val, SQLLEN* _len);
	bool BindParam(int32_t _idx, float* _val, SQLLEN* _len);
	bool BindParam(int32_t _idx, double* _val, SQLLEN* _len);
	bool BindParam(int32_t _idx, int8_t* _val, SQLLEN* _len);
	bool BindParam(int32_t _idx, int16_t* _val, SQLLEN* _len);
	bool BindParam(int32_t _idx, int32_t* _val, SQLLEN* _len);
	bool BindParam(int32_t _idx, int64_t* _val, SQLLEN* _len);
	bool BindParam(int32_t _idx, TIMESTAMP_STRUCT* _val, SQLLEN* _len);
	bool BindParam(int32_t _idx, const char* _val, SQLLEN* _len);
	bool BindParam(int32_t _idx, const BYTE* _val, int32_t _size, SQLLEN* _len);
public:
	bool BindCol(int32_t _idx, bool* _val, SQLLEN* _len);
	bool BindCol(int32_t _idx, float*_val, SQLLEN* _len);
	bool BindCol(int32_t _idx, double*_val, SQLLEN* _len);
	bool BindCol(int32_t _idx, int8_t*_val, SQLLEN* _len);
	bool BindCol(int32_t _idx, int16_t*_val, SQLLEN* _len);
	bool BindCol(int32_t _idx, int32_t*_val, SQLLEN* _len);
	bool BindCol(int32_t _idx, int64_t*_val, SQLLEN* _len);
	bool BindCol(int32_t _idx, TIMESTAMP_STRUCT* _val, SQLLEN* _len);
	bool BindCol(int32_t _idx, char*_val, int32_t _size, SQLLEN* _len);
	bool BindCol(int32_t _idx, BYTE*_val, int32_t _size, SQLLEN* _len);
public:
	int8_t GetInt8(int _colNo);
	int16_t GetInt16(int _colNo);
	int32_t GetInt32(int _colNo);
	int64_t GetInt64(int _colNo);

	bool GetBool(int _colNo);

	double GetDouble(int _colNo);
	float GetFloat(int _colNo);

	string&& GetStr(int _colNo);
	string&& GetStrLong(int _colNo);

};
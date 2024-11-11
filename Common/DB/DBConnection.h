#pragma once


class DBConnection
{
private:
	SQLHDBC hdbc = SQL_NULL_HANDLE;
	SQLHSTMT statement = SQL_NULL_HANDLE;
public:
	bool Connect(SQLHENV _henv, const char* _connStr);
	bool Connect(SQLHENV _henv, string _odbcName, string _host, string _user, string _pwd, int32_t dbNameVal, int32_t rwVal);
	void Clear();
	bool Execute(const char* _sql);
	bool Fetch();
	int32_t GetRowCount();
	void Unbind();
public:
	bool BindParam(SQLUSMALLINT _paramIdx, SQLSMALLINT _cType, SQLSMALLINT _sqlType
		, SQLULEN _len, SQLPOINTER _ptr, SQLLEN* _idx
	);
	bool BindCol(SQLUSMALLINT _conIdx, SQLSMALLINT _cType, SQLULEN len, SQLPOINTER _val, SQLLEN* _idx);
	void HandleError(SQLRETURN _ret);
};
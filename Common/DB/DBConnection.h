#pragma once


class DBConnection 
{
private:
	SQLHDBC conn = SQL_NULL_HANDLE;
	SQLHSTMT statement = SQL_NULL_HANDLE;
public:
	bool Connect(SQLHENV _henv, const char* _connStr);
	void Clear();
	bool Execute(const char* _sql);
	bool Fetch();
	int32_t GetRowCount();
	void Unbind();
public:
	bool BindParam(SQLUSMALLINT _paramIdx, SQLSMALLINT _cType, SQLSMALLINT _sqlType
		, SQLULEN _len, SQLPOINTER _ptr, SQLLEN* _idx
	);
	bool BindCol(SQLUSMALLINT _conIdx, SQLSMALLINT _cType, SQLPOINTER _val, SQLLEN* _idx);
	void HandleError(SQLRETURN _ret);
};
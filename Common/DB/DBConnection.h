#pragma once

#include <sql.h>
#include <sqlext.h>

class DBConnection
{
public:
	
private:
	SQLHDBC conn = SQL_NULL_HANDLE;
	SQLHSTMT state = SQL_NULL_HANDLE;
public:
	bool Connect(SQLHENV* _henv, string connStr);
	void Clear();

	bool Execute(string _query);
	bool fetch();
	int32_t GetRowCount();
	void Unbind();
public:
	bool BindParam(SQLUSMALLINT _paramIdx, SQLSMALLINT _cType
		, SQLSMALLINT _sqlType, SQLULEN _len, SQLPOINTER _ptr, SQLLEN* _index
	);

	bool BindCol(SQLUSMALLINT _columnIdx, SQLSMALLINT _cType, SQLULEN _len
		, SQLPOINTER _val, SQLLEN* _idx
	);

	void HandleError(SQLRETURN _ret);

};
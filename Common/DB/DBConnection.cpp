#include "pch.h"
#include "DBConnection.h"

bool DBConnection::Connect(SQLHENV _henv, const char* _connStr)
{
	if(SQLAllocHandle(SQL_HANDLE_DBC, _henv, &conn) != SQL_SUCCESS) {
		return false;
	}

	array<char, MAX_PATH> strBuf = {0, };
	std::strncpy(strBuf.data(), _connStr, strBuf.size());

	array<char, MAX_PATH> retStr = {0, };
	SQLSMALLINT retLen = 0;
	SQLDriverConnectA(conn, NULL, reinterpret_cast<SQLCHAR*>(strBuf.data()), strBuf.size()
		, OUT reinterpret_cast<SQLCHAR*>(retStr.data()), retStr.size()
		, OUT &retLen,  SQL_DRIVER_NOPROMPT
	);
	return true;
}

void DBConnection::Clear()
{
}

bool DBConnection::Execute(const char* _sql)
{
	return false;
}

bool DBConnection::Fetch()
{
	return false;
}

int32_t DBConnection::GetRowCount()
{
	return 0;
}

void DBConnection::Unbind()
{
}

bool DBConnection::BindParam(SQLUSMALLINT _paramIdx, SQLSMALLINT _cType, SQLSMALLINT _sqlType, SQLULEN _len, SQLPOINTER _ptr, SQLLEN* _idx)
{
	return false;
}

bool DBConnection::BindCol(SQLUSMALLINT _conIdx, SQLSMALLINT _cType, SQLPOINTER _val, SQLLEN* _idx)
{
	return false;
}

void DBConnection::HandleError(SQLRETURN _ret)
{
}

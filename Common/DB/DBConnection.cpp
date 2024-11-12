#include "pch.h"
#include "DBConnection.h"

bool DBConnection::Connect(SQLHENV _henv, const char* _connStr)
{
	if(SQLAllocHandle(SQL_HANDLE_DBC, _henv, &hdbc) != SQL_SUCCESS) {
		return false;
	}

	array<char, MAX_PATH> strBuf = {0, };
	int len = strlen(_connStr);
	strncpy_s(strBuf.data(), strBuf.size(), _connStr, len);

	array<char, MAX_PATH> retStr = {0, };
	SQLSMALLINT retLen = 0;
	SQLRETURN ret = SQLDriverConnectA(hdbc, NULL, reinterpret_cast<SQLCHAR*>(strBuf.data()), strBuf.size()
		, OUT reinterpret_cast<SQLCHAR*>(retStr.data()), retStr.size()
		, OUT &retLen,  SQL_DRIVER_NOPROMPT
	);

	if(SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &statement) != SQL_SUCCESS) {
		return false;
	}

	return (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO);
}

bool DBConnection::Connect(SQLHENV _henv, string _odbcName, string _host, string _user, string _pwd, int32_t dbNameVal, int32_t rwVal)
{
	SQLSMALLINT retLen = 0;

	SQLRETURN ret = SQLAllocHandle(SQL_HANDLE_DBC, _henv, &hdbc);
	if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
		printf("SQL Return : %d\n", ret);
		return false;
	}

	ret = SQLConnectA(hdbc, (SQLCHAR*)_odbcName.c_str(), SQL_NTS
		, (SQLCHAR*)_user.c_str(), SQL_NTS
		, (SQLCHAR*)_pwd.c_str(), SQL_NTS
	);
	if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
		HandleError(ret);
		printf("SQL Return : %d\n", ret);
		return false;
	}
	ret = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &statement);
	if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
		HandleError(ret);
		printf("SQL Return : %d\n", ret);
		return false;
	}
	return true;
}

void DBConnection::Clear()
{
	if(hdbc != SQL_NULL_HANDLE) {
		SQLFreeHandle(SQL_HANDLE_DBC, hdbc) ;
		hdbc = SQL_NULL_HANDLE;
	}
	
	if (statement != SQL_NULL_HANDLE) {
		SQLFreeHandle(SQL_HANDLE_STMT, statement);
		statement = SQL_NULL_HANDLE;
	}

}

bool DBConnection::Execute(const char* _sql)
{
	SQLRETURN ret = SQLExecDirectA(statement, (SQLCHAR*)_sql, SQL_NTSL);
	if(ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
		HandleError(ret);
		return false;
	} 
	return true;
}

bool DBConnection::Fetch()
{
	SQLRETURN ret = SQLFetch(statement);

	switch(ret) {
	case SQL_SUCCESS: 
	case SQL_SUCCESS_WITH_INFO: {
		return true;
	}
	case SQL_NO_DATA: {
		return false;
	}
	case SQL_ERROR: {
		HandleError(ret);
		return false;
	}
	default: {
		return true;
	}
	}
}

int32_t DBConnection::GetRowCount()
{
	SQLLEN cnt = 0;
	SQLRETURN ret = SQLRowCount(statement, OUT &cnt);
	if(ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
		return static_cast<int32_t>(cnt);
	}
	return -1;
}

void DBConnection::Unbind()
{
	SQLFreeStmt(statement, SQL_UNBIND);
	SQLFreeStmt(statement, SQL_RESET_PARAMS);
	SQLFreeStmt(statement, SQL_CLOSE);
}

bool DBConnection::BindParam(SQLUSMALLINT _paramIdx, SQLSMALLINT _cType, SQLSMALLINT _sqlType, SQLULEN _len, SQLPOINTER _ptr, SQLLEN* _idx)
{
	SQLRETURN ret = SQLBindParameter(statement, _paramIdx, SQL_PARAM_INPUT, _cType, _sqlType, _len, 0, _ptr, 0, _idx);
	if(ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
		HandleError(ret);
		return false;
	}
	return true;
}

bool DBConnection::BindCol(SQLUSMALLINT _columnIdx, SQLSMALLINT _cType, SQLULEN _len, SQLPOINTER _val, SQLLEN* _idx)
{
	SQLRETURN ret = SQLBindCol(statement, _columnIdx, _cType, _val, _len, _idx);
	if(ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
		HandleError(ret);
		return false;
	}

	return true;
}

void DBConnection::HandleError(SQLRETURN _ret)
{
	if(_ret == SQL_SUCCESS || _ret == SQL_SUCCESS_WITH_INFO) {
		return ;
	}

	SQLSMALLINT idx = 1;
	array<SQLCHAR, MAX_PATH> sqlState = {0, };
	SQLINTEGER nativeError = 0;
	array<SQLCHAR, MAX_PATH> errMsg = {0, };
	SQLSMALLINT msgLen = 0;
	SQLRETURN errRet = 0;
	while(true) {
		SQLGetDiagRecA(SQL_HANDLE_STMT
			,  statement
			, idx, sqlState.data()
			, OUT &nativeError
			, errMsg.data(), errMsg.size()
			, OUT &msgLen
		);

		if(errRet == SQL_NO_DATA) {
			break;
		}

		if(errRet != SQL_SUCCESS) {
			break;
		}

		cout.imbue(locale("kor"));
		cout << errMsg.data() << endl;
		idx++;
	}
}

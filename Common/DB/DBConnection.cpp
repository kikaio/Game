#include "pch.h"
#include "DBConnection.h"

bool DBConnection::Connect(SQLHENV* _henv, string _connStr)
{
	if(::SQLAllocHandle(SQL_HANDLE_DBC, _henv, &conn) != SQL_SUCCESS) {
		return false;
	}

	vector<char> _tmpVect(_connStr.begin(), _connStr.end());

	array<char, MAX_PATH> retStr = {0, };

	SQLSMALLINT retStrLen = 0;

	SQLRETURN ret = SQLDriverConnectA(
		conn
		, NULL
		, reinterpret_cast<SQLCHAR*>(_tmpVect.data())
		, _tmpVect.size()
		, OUT reinterpret_cast<SQLCHAR*>(retStr.data())
		, retStr.size()
		, OUT &retStrLen
		, SQL_DRIVER_PROMPT
	);

	if(::SQLAllocHandle(SQL_HANDLE_STMT, conn, &state) != SQL_SUCCESS) {
		return false;
	}

	return (ret == SQL_SUCCESS) || (ret == SQL_SUCCESS_WITH_INFO);
}

void DBConnection::Clear()
{
	if(conn != SQL_NULL_HANDLE) {
		::SQLFreeHandle(SQL_HANDLE_DBC, conn);
		conn = SQL_NULL_HANDLE;
	}

	if(state != SQL_NULL_HANDLE) {
		::SQLFreeHandle(SQL_HANDLE_STMT, state);
		state = SQL_NULL_HANDLE;
	}

	return ;
}

bool DBConnection::Execute(string _query)
{
	SQLRETURN ret = ::SQLExecDirectA(
		state, (SQLCHAR*)(_query.data()), SQL_NTSL
	);
	
	if(ret != SQL_SUCCESS && ret !=SQL_SUCCESS_WITH_INFO) {
		HandleError(ret);
		return false;
	}
	return true;
}

bool DBConnection::fetch()
{
	SQLRETURN ret = ::SQLFetch(state);

	switch(ret) {
	case SQL_SUCCESS_WITH_INFO:
	case SQL_SUCCESS: {
		return true;
	}
	case SQL_NO_DATA: {
		return false;
	}
	case SQL_ERROR: {
		HandleError(ret);
		return false;
	}
	}
	return true;
}

int32_t DBConnection::GetRowCount()
{
	SQLLEN cnt = 0;
	SQLRETURN ret = ::SQLRowCount(state, OUT &cnt);

	if(ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
		return static_cast<int32_t>(cnt);
	}

	return -1;
}

void DBConnection::Unbind()
{
	SQLFreeStmt(state, SQL_UNBIND);
	SQLFreeStmt(state, SQL_RESET_PARAMS);
	SQLFreeStmt(state, SQL_CLOSE);



	return ;
}

bool DBConnection::BindParam(SQLUSMALLINT _paramIdx, SQLSMALLINT _cType
	, SQLSMALLINT _sqlType, SQLULEN _len, SQLPOINTER _ptr, SQLLEN* _index
)
{
	SQLRETURN ret =  ::SQLBindParameter(state, _paramIdx, SQL_PARAM_INPUT
		, _cType, _sqlType, _len, 0, _ptr, 0, _index
	);
	if(ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
		HandleError(ret);
		return false;
	}


	return true;
}

bool DBConnection::BindCol(SQLUSMALLINT _columnIdx, SQLSMALLINT _cType
	, SQLULEN _len, SQLPOINTER _val, SQLLEN* _idx
)
{
	SQLRETURN ret = ::SQLBindCol(state, _columnIdx, _cType, _val, _len, _idx);
	if(ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
		HandleError(ret);
		return false;
	}
	return true;
}

void DBConnection::HandleError(SQLRETURN _ret)
{
	switch(_ret) {
	case SQL_SUCCESS: {
		return ;
	}
	case SQL_SUCCESS_WITH_INFO: {
		return ;
	}
	default : {
		SQLSMALLINT idx = 1;
		array<SQLCHAR, _MAX_PATH> sqlState = {0, };
		SQLINTEGER nativeErr = 0;
		array<SQLCHAR, MAX_PATH> errMsg = {0, };
		SQLSMALLINT msgLen = 0;
		SQLRETURN errorRet = 0;
		while(true) {
			errorRet = ::SQLGetDiagRecA(
				SQL_HANDLE_STMT
				, state
				, idx
				, sqlState.data()
				, OUT &nativeErr
				, errMsg.data()
				, errMsg.size()
				, OUT &msgLen
			);

			if(errorRet == SQL_NO_DATA) {
				break;
			}
			if(errorRet == SQL_SUCCESS || errorRet == SQL_SUCCESS_WITH_INFO) {
				break;
			}

			//todo : logging
			cout.imbue(locale("kor"));
			cout << errMsg.data() <<endl;

			idx++;
		}
	}
	}
	return ;
}

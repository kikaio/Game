#pragma once

class DBQuery
{
public:
	DBQuery(DBConn& _conn, const char* _qeury);
	DBQuery(DBConn& _conn, string _qeury);
	virtual ~DBQuery();
private:
	sql::PreparedStatement* preparedState = nullptr;
	DBConn& conn;
	int colNo = 0;
	bool isEnd = false;
public:
	bool Execute();
	void ExecuteQuery(DBResultSet& _ret);
	void ExecuteQuery(DBResultSet& _ret, const char* _q, ...);
public:
	bool GetMoreResults(DBResultSet& _ret);
	void Clear();
	void ClearResultSet();
};

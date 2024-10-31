#pragma once


class DBResultSet
{
public:
	DBResultSet();
	~DBResultSet();
private:
	sql::Connection* conn = nullptr;
	sql::ResultSet* retSet = nullptr;
public:
	void SetResultSet(sql::ResultSet* _ret);
	void SetConn(sql::Connection* _conn);
	bool Next();
public:
	string GetStr(const char* _col);
	float GetFloat(const char* _col);
	double GetDouble(const char* _col);
	uint64_t GetUint64(const char* _col);
	uint32_t GetUint32(const char* _col);
	int64_t GetInt64(const char* _col);
	int32_t GetInt32(const char* _col);
	time_t GetTime(const char* _col);
	tm GetTM(const char* _col);
	bool GetBool(const char* _col);
	
};
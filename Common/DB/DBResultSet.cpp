#include "pch.h"
#include "DBResultSet.h"

DBResultSet::DBResultSet()
{
}

DBResultSet::~DBResultSet()
{
}

void DBResultSet::SetResultSet(sql::ResultSet* _ret)
{
	retSet = _ret;
}

bool DBResultSet::HasNext()
{
	return ;
}

string DBResultSet::GetStr(const char* _col)
{
	return string();
}

float DBResultSet::GetFloat(const char* _col)
{
	return 0.0f;
}

double DBResultSet::GetDouble(const char* _col)
{
	return 0.0;
}

uint64_t DBResultSet::GetUint64(const char* _col)
{
	return 0;
}

uint32_t DBResultSet::GetUint32(const char* _col)
{
	return 0;
}

int64_t DBResultSet::GetInt64(const char* _col)
{
	return 0;
}

int32_t DBResultSet::GetInt32(const char* _col)
{
	return 0;
}

time_t DBResultSet::GetTime(const char* _col)
{
	return time_t();
}

tm DBResultSet::GetTM(const char* _col)
{
	return tm();
}

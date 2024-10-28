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
	return retSet->next();
}

string DBResultSet::GetStr(const char* _col)
{
	return retSet->getString(_col);
}

float DBResultSet::GetFloat(const char* _col)
{
	return static_cast<float>(retSet->getDouble(_col));
}

double DBResultSet::GetDouble(const char* _col)
{
	return retSet->getDouble(_col);
}

uint64_t DBResultSet::GetUint64(const char* _col)
{
	return retSet->getUInt64(_col);
}

uint32_t DBResultSet::GetUint32(const char* _col)
{
	return retSet->getUInt(_col);
}

int64_t DBResultSet::GetInt64(const char* _col)
{
	return retSet->getInt64(_col);
}

int32_t DBResultSet::GetInt32(const char* _col)
{
	return retSet->getInt(_col);
}

time_t DBResultSet::GetTime(const char* _col)
{
	return retSet->getInt64(_col);
}

tm DBResultSet::GetTM(const char* _col)
{
	auto timeT = GetTime(_col);
	tm curTm;
	localtime_s(&curTm, &timeT);
	return curTm;
}

bool DBResultSet::GetBool(const char* _col)
{
	return retSet->getBoolean(_col);
}

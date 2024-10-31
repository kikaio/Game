#include "pch.h"
#include "DBQuery.h"

DBQuery::DBQuery(DBConn& _conn, const char* _query)
    : conn(_conn)
{
    preparedState = conn.GetConn()->prepareStatement(_query);
}

DBQuery::DBQuery(DBConn& _conn, string _query)
    : conn(_conn)
{
    preparedState = conn.GetConn()->prepareStatement(_query.c_str());
}

DBQuery::~DBQuery()
{
    try {
        if (isEnd) {
            Clear();
        }
    }
    catch (sql::SQLException e) {
        //todo : logging
    }
    catch (...) {
        //todo : logging
    }
}

bool DBQuery::Execute()
{
    colNo = 0;

    return preparedState->execute();   
}

void DBQuery::ExecuteQuery(DBResultSet& _ret)
{
    colNo = 0;
    _ret.SetResultSet(preparedState->executeQuery());
    _ret.SetConn(conn.GetConn());
}

void DBQuery::ExecuteQuery(DBResultSet& _ret, const char* _q, ...)
{
    array<char, BUF_256> buf = {0, };
    va_list vaList;
    va_start(vaList, _q);
    vsnprintf(buf.data(), BUF_256 - 1, _q, vaList);
    va_end(vaList);
    colNo = 0;
    _ret.SetResultSet(preparedState->executeQuery(_q));
}

bool DBQuery::GetMoreResults(DBResultSet& _ret)
{
    bool flag = false;
    try {
        flag = preparedState->getMoreResults();
        if (flag) {
            _ret.SetResultSet(preparedState->getResultSet());
        }
    }
    catch (sql::SQLException e) {
        isEnd = true;
        throw;
    }

    return flag;
}

void DBQuery::Clear()
{
    ClearResultSet();
    isEnd = true;
}

void DBQuery::ClearResultSet()
{
    if (preparedState == nullptr) {
        return;
    }

    DBResultSet ret;
    while (GetMoreResults(ret)) {
    }
}

#include "pch.h"
#include "DBLink.h"

DBLink::~DBLink()
{
	if(IsNull() == false && commitType == ECommitType::MANUAL) {
		if(commited == false) {
			RollBack();
		}
	}
}

void DBLink::Init()
{
	// todo : do job for some init...
	if(IsNull() == false) {
		conn.GetConn()->setAutoCommit(commitType == ECommitType::AUTO);
	}
}

bool DBLink::IsNull()
{
	return conn.GetConn() == nullptr;
}

sql::Statement* DBLink::creaetStatement()
{
	return IsNull() ? nullptr : conn.GetConn()->createStatement();
}

sql::PreparedStatement* DBLink::PrepareStatement(const char* _stmt)
{
	return IsNull() ? nullptr : conn.GetConn()->prepareStatement(_stmt);
}

sql::PreparedStatement* DBLink::PrepareStatement(const string& _str)
{
	return IsNull() ? nullptr : conn.GetConn()->prepareStatement(_str);
}

void DBLink::Commit()
{
	switch(commitType) {
	case ECommitType::MANUAL: {
		conn.GetConn()->commit();
		commited = true;
		break;
	}
	default: {
		//todo : logging for warning
		printf("check this Link's commit type.!!!");
		break;
	}
	}
}

void DBLink::RollBack()
{
	if(IsNull()) {
		return ;
	}
	if(rollbacked) {
		return ;
	}
	rollbacked = true;
	try {
		conn.GetConn()->rollback();
	}
	catch(sql::SQLException e) {
		//todo : logging error
		return ;
	}
}

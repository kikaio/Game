#pragma once

class DBLink
{
public:
	enum class ECommitType {
		AUTO
		, MANUAL
	};
public:
	DBLink(DBConn& _conn, ECommitType _commitType = ECommitType::AUTO) : conn(_conn) , commitType(_commitType){
		Init();
	}
	DBLink(const DBLink& _other) = delete;
	~DBLink();
private:
	DBConn& conn;
	ECommitType commitType;
	bool commited = false;
	bool rollbacked = false;
public:
	void Init();
public:
	void SetCommitType(ECommitType _commitTYpe) {
		commitType = _commitTYpe;
	}
	const DBConn& GetDBConnection() {
		return conn;
	}
public:
	bool IsNull();
	sql::Statement* creaetStatement();
	sql::PreparedStatement* PrepareStatement(const char* _stmt);
	sql::PreparedStatement* PrepareStatement(const string& _str);
	void Commit();
	void RollBack();
};
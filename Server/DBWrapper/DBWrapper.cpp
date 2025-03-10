#include "pch.h"
#include "DBWrapper.h"


int32_t DBWrapper::DoDatabaseTest()
{
    auto sql = "DROP TABLE IF EXISTS `Gold`";
    auto sql2 = "CREATE TABLE `Gold`                    \
    (                                                   \
        `id` INT NOT NULL PRIMARY KEY AUTO_INCREMENT,   \
        `gold` INT NOT NULL DEFAULT 0,                  \
        `name` varchar(500) DEFAULT NULL,                \
        `cDate` DATETIME DEFAULT NULL                   \
    );                                                  \
    ";

    {
        DBConnectionSptr conn = DBConnectionPool::Get().PopCommonDB(RWType::READ_WRITE);
        ASSERT_CRASH(conn != nullptr);
        ASSERT_CRASH(conn->Execute(sql));
        conn->Unbind();
        ASSERT_CRASH(conn->Execute(sql2));
        conn->Unbind();
    }

    for (int32_t idx = 0; idx < 3; idx++) {
        DBConnectionSptr conn = DBConnectionPool::Get().PopCommonDB(RWType::READ_WRITE);
        ASSERT_CRASH(conn != nullptr);

        DBBind<3, 0> bind(*conn, "INSERT INTO `gold` (`gold`, `name`, `cDate`) VALUES (?, ?, ?);");
        int gold = 100;
        char name[500] = "testName";
        TIMESTAMP_STRUCT ts = { 2024, 11, 24 };
        bind.BindParam(0, gold);
        bind.BindParam(1, name);
        bind.BindParam(2, ts);
        ASSERT_CRASH(bind.Execute());
    }

    {
        DBConnectionSptr conn = DBConnectionPool::Get().PopCommonDB(RWType::READ_WRITE);

        DBBind<1, 4> bind(*conn, "SELECT id, gold, name, cDate FROM `gold` WHERE gold = (?);");

        int32_t targetGold = 100;
        bind.BindParam(0, targetGold);

        int32_t outId = 0;
        int32_t outGold = 0;
        char outName[500] = { 0, };
        TIMESTAMP_STRUCT outTs = {};

        bind.BindCol(0, OUT outId);
        bind.BindCol(1, OUT outGold);
        bind.BindCol(2, OUT outName);
        bind.BindCol(3, OUT outTs);

        ASSERT_CRASH(bind.Execute());
        while (bind.Fetch()) {
            printf("cur Id : %d, gold : %d\n", outId, outGold);
            printf("cur name : %s, year : %d, month : %d, day : %d\n", outName, outTs.year, outTs.month, outTs.day);
        }
    }
    DBConnectionPool::Get().Clear();

    return 0;
}

PacketError DBWrapper::SelectPlatform(const LoginData& _loginData)
{
    DBConnectionSptr conn = DBConnectionPool::Get().PopCommonDB(RWType::READ_WRITE);
    DBBind<2, 6> dbBinder(*conn, "call usp_platform_select(?, ?);");

    dbBinder.BindParam(0, IN _loginData.sId.c_str());
    dbBinder.BindParam(1, IN ENUM_TO_INT(_loginData.loginPlatform));
    {
        int32_t curColIdx = 0;
        PlatformRow platrofmRow;
        
        //col별로 변수에 연결해준다.
        platrofmRow.FromDB(dbBinder, curColIdx, OUT curColIdx);
        if(dbBinder.Execute() == false) {
            GS_ERROR_LOG("call usp_platform_select failed. param : {}, {}", _loginData.sId.c_str(), ENUM_TO_INT(_loginData.loginPlatform));
            return MAKE_PACKET_ERROR(ERR_CATEGORY::DB, DB_ERR_DETAIL::PROCEDURE_FAILED);
        }
        
        while(dbBinder.Fetch()) {
            GS_DEBUG_LOG("cur platform pid : {}, sid : {}, aid : {}", platrofmRow.pId, platrofmRow.sId, platrofmRow.aId);
        }
    }


    return PacketError();
}
PacketError DBWrapper::SelectAccount(const LoginData& _loginData)
{
    auto conn = DBConnectionPool::Get().PopCommonDB(RWType::READ_WRITE);
    if (conn == nullptr) {
        return MAKE_PACKET_ERROR(ERR_CATEGORY::DB, DB_ERR_DETAIL::CONN_FAILED);
    }
    // todo : call procedure 'select_account'
    return PacketError();
}

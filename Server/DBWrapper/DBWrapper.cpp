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

PacketError DBWrapper::PlatformSelect(const LoginData& _loginData, GameUserSptr _gameUser, bool& _is_old_user, int32_t _def_main_hero_id, int32_t _def_main_frame_id, string _def_main_greeting_ment)
{
    DBConnectionSptr conn = DBConnectionPool::Get().PopCommonDB(RWType::READ_WRITE);
    DBBind<5, 0> dbBinder(*conn, "call usp_platform_select(?, ?, ?, ?, ?);");
    
    int32_t platformVal = ENUM_TO_INT(_loginData.loginPlatform);
    dbBinder.BindParam(0, IN _loginData.sId.c_str());
    dbBinder.BindParam(1, IN platformVal);
    dbBinder.BindParam(2, IN _def_main_hero_id);
    dbBinder.BindParam(3, IN _def_main_frame_id);
    dbBinder.BindParam(4, IN _def_main_greeting_ment.c_str());

    {
        if (dbBinder.Execute() == false) {
            GS_ERROR_LOG("call usp_platform_select failed. param : {}, {}", _loginData.sId.c_str(), ENUM_TO_INT(_loginData.loginPlatform));
            return MAKE_PACKET_ERROR(ERR_CATEGORY::DB, DB_ERR_DETAIL::PROCEDURE_FAILED);
        }

        PlatformRow platformRow;
        AccountRow accountRow;
        SummaryRow summaryRow;
        ProfileRow profileRow;
        while (dbBinder.Fetch()) {

            int32_t curColNo = 1;

            // false : 해당 유저가 신규 생성된 유저인 경우
            dbBinder.GetBool(curColNo++, OUT _is_old_user);

            platformRow.FromDB(dbBinder, curColNo, OUT curColNo);
            accountRow.FromDB(dbBinder, curColNo, OUT curColNo);
            summaryRow.FromDB(dbBinder, curColNo, OUT curColNo);
            profileRow.FromDB(dbBinder, curColNo, OUT curColNo);


            GameProfile& profile = _gameUser->GetProfile();

            _gameUser->SetAccountId(platformRow.aId);
            profile.ChangeGreetingMent(profileRow.greetingMent);
            profile.ChangeMainHeroId(profileRow.mainHeroId);
            profile.ChangeMainFrameId(profileRow.mainFrameId);
        }
    }


    return PacketError();
}

PacketError DBWrapper::GameUserCreate(GameUserSptr _gameUser) {

    // todo : aid 를 기준으로 신규 data를 생성하는 procedure 호출.
    auto conn = DBConnectionPool::Get().PopGameDB();
    if(conn == nullptr) {
        GS_DEBUG_LOG("db connection pool is empty, check this. - CreateGame");
        return MAKE_PACKET_ERROR(ERR_CATEGORY::DB, DB_ERR_DETAIL::CONNECTION_NOT_EXIST);
    }

    DBBind<4, 0> binder(*conn, "call usp_gameuser_create(?, ?, ?, ?)");
    int64_t accountId = _gameUser->GetAccountId();
    //기본적으로 지급해야 하는 character에 대한 basis id들의 연결된 문자열
    string def_character_str = "12_34_56";
    //기본적으로 지급해야 하는 item에 대한 basis id들의 연결된 문자열
    string def_item_str = "1_2_3_4_5";
    //기본적으로 지급해야 하는 costume에 대한 basis id들의 연결된 문자열
    string def_costume_str = "1234_5678";

    binder.BindParam(0, accountId);
    binder.BindParam(1, def_character_str.c_str());
    binder.BindParam(2, def_item_str.c_str());
    binder.BindParam(3, def_costume_str.c_str());

    if(binder.Execute() == false) {
        return MAKE_PACKET_ERROR(ERR_CATEGORY::DB, DB_ERR_DETAIL::EXECUTE_FAILED);
    }
    
    return PacketError();
}

PacketError DBWrapper::GameUserSelect(GameUserSptr _gameUser) {

    //todo : select game user
    auto conn = DBConnectionPool::Get().PopGameDB();
    if(conn == nullptr) {
        GS_ERROR_LOG("db conn pool is empty, check this, - SelectGameUser");
        return MAKE_PACKET_ERROR(ERR_CATEGORY::DB, DB_ERR_DETAIL::CONNECTION_NOT_EXIST);
    }

    DBBind<1,0> binder(*conn, "call usp_gameuser_select(?)");
    int64_t accountId = _gameUser->GetAccountId();
    binder.BindParam(0, accountId);

    if(binder.Execute() == false) {
        return MAKE_PACKET_ERROR(ERR_CATEGORY::DB, DB_ERR_DETAIL::CONNECTION_NOT_EXIST);
    }

    // gameuser select
    while(binder.Fetch()) {
        GameUserRow row;
        row.FromDB(binder);
    }

    ASSERT_CRASH(binder.HasNext());
    
    //characters -> 수집형 RPG의 영웅
    while(binder.Fetch()) {
        CharacterRow row;
        row.FromDB(binder);
    }

    ASSERT_CRASH(binder.HasNext());

    //items
    while(binder.Fetch()) {
        ItemRow row;
        row.FromDB(binder);
    }

    ASSERT_CRASH(binder.HasNext());

    //costumes
    while (binder.Fetch()) {
        CostumeRow row;
        row.FromDB(binder);
    }

    return PacketError();
}
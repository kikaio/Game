#include "pch.h"
#include "ClientConfig.h"

int32_t ClientConfig::DummyCnt()
{
    return dummyCnt;
}

const string& ClientConfig::LoggerLv()
{
    return loggerLv;
}

int32_t ClientConfig::WorkerThreadCnt()
{
    return workerThreadCnt;
}

void ClientConfig::Init(const rapidjson::Value& _val)
{
    ASSERT_CRASH(_val.HasMember("dummy_cnt"));
    ASSERT_CRASH(_val.HasMember("logger_lv"));
    ASSERT_CRASH(_val.HasMember("worker_thread_cnt"));

    dummyCnt = _val["dummy_cnt"].GetInt();
    workerThreadCnt = _val["worker_thread_cnt"].GetInt();
    loggerLv = _val["logger_lv"].GetString();
}

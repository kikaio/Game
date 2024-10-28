#include "pch.h"
#include "DBManager.h"

void DBManager::Test()
{
    try {
        // MySQL 드라이버 인스턴스를 가져옵니다.
        sql::Driver* driver = get_driver_instance();

        // 데이터베이스에 연결합니다.
        const string server = "tcp://127.0.0.1:3306";
        const string name = "root";
        const string password = "";
        std::unique_ptr<sql::Connection> conn(driver->connect(server, name, password));

        // 데이터베이스 작업을 수행합니다.
        conn->setSchema("testdb");

        // 쿼리 실행
        std::unique_ptr<sql::Statement> stmt(conn->createStatement());
        std::unique_ptr<sql::ResultSet> res(stmt->executeQuery("SELECT * FROM user"));

        // 결과 처리
        while (res && res->next()) {
            std::cout << res->getString(1) << " " << res->getString(2) << std::endl;
        }

    }
    catch (sql::SQLException& e) {
        std::cerr << "SQLException: " << e.what() << std::endl;
        std::cerr << "Error code: " << e.getErrorCode() << std::endl;
        std::cerr << "SQL state: " << e.getSQLState() << std::endl;
    }
    catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
    catch (...) {
        std::cerr << "Unknown exception occurred" << std::endl;
    }
}

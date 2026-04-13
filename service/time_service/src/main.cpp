#include "repository/PostgresTimeRepository.cpp"
#include "service/TimeService.h"
#include "controller/TimeRestController.cpp"
#include <cstdlib>
#include <iostream>

using namespace std;

int main() {
    const char* dbHost = getenv("DB_HOST");
    const char* dbPort = getenv("DB_PORT");
    const char* dbUser = getenv("DB_USER");
    const char* dbPass = getenv("DB_PASSWORD");
    const char* dbName = getenv("DB_NAME");

    if (!dbHost || !dbPort || !dbUser || !dbPass || !dbName) {
        cerr << "CRITICAL: Database environment variables are missing!" << endl;
        return 1;
    }

    string conn_str = "host=" + string(dbHost) +
                      " port=" + string(dbPort) +
                      " user=" + string(dbUser) +
                      " password=" + string(dbPass) +
                      " dbname=" + string(dbName);

    try {
        PostgresTimeRepository repo(conn_str);
        TimeService service(repo);
        TimeRestController controller(service);

        controller.run(80);

    } catch (const exception& e) {
        cerr << "Application crashed: " << e.what() << endl;
        return 1;
    }

    return 0;
}
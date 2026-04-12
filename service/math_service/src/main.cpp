#include "repository/PostgresMathRepository.h"
#include "service/MathService.h"
#include "controller/MathRestController.h"
#include <cstdlib>
#include <iostream>

int main() {
    const char* dbHost = std::getenv("DB_HOST");
    const char* dbPort = std::getenv("DB_PORT");
    const char* dbUser = std::getenv("DB_USER");
    const char* dbPass = std::getenv("DB_PASSWORD");
    const char* dbName = std::getenv("DB_NAME");

    if (!dbHost || !dbPort || !dbUser || !dbPass || !dbName) {
        std::cerr << "CRITICAL: Database environment variables are missing!\n";
        return 1;
    }

    std::string conn_str = "host=" + std::string(dbHost) +
                           " port=" + std::string(dbPort) +
                           " user=" + std::string(dbUser) +
                           " password=" + std::string(dbPass) +
                           " dbname=" + std::string(dbName);

    try {
        PostgresMathRepository repo(conn_str);
        MathService service(repo);
        MathRestController controller(service);

        controller.run(80);
    } catch (const std::exception& e) {
        std::cerr << "Application crashed: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
#include "PostgresMathRepository.h"
#include <pqxx/pqxx>
#include "iostream"

PostgresMathRepository::PostgresMathRepository(const std::string& connection_string) : conn_str(connection_string) {}

void PostgresMathRepository::saveOperation(const std::string& opName, const std::string& inputJson, const std::string& result) {
    try {
        pqxx::connection conn(conn_str);
        pqxx::work txn(conn);
        txn.exec_params(
            "INSERT INTO math_operations (operation_name, input_data, result) VALUES ($1, $2, $3)",
            opName, inputJson, result
        );
        txn.commit();
    } catch (const std::exception& e) {
        std::cerr << "DB Error: " << e.what() << std::endl;
        throw;
    }
}
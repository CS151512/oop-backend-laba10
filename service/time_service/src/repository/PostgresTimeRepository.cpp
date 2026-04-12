#pragma once
#include "ITimeRepo.h"
#include <pqxx/pqxx>
#include <string>
#include <iostream>
#include <sstream>

class PostgresTimeRepository : public ITimeRepository {
private:
    std::string conn_str;

public:
    PostgresTimeRepository(const std::string& connection_string) : conn_str(connection_string) {}

    void update(int id, const Time& time) override {
        try {
        pqxx::connection conn(conn_str);
        pqxx::work txn(conn);

        std::ostringstream oss;
        oss << time;

        txn.exec_params(
            "UPDATE time_records SET hours = $1, minutes = $2, seconds = $3, formatted_time = $4 WHERE id = $5",
            time.toSeconds() / 3600,
            (time.toSeconds() % 3600) / 60,
            time.toSeconds() % 60,
            oss.str(),
            id
        );
        txn.commit();
        } catch (const std::exception& e) {
            std::cerr << "DB Update Error: " << e.what() << std::endl;
            throw;
        }
    }

    int save(const Time& time) override {
        try {
        pqxx::connection conn(conn_str);
        pqxx::work txn(conn);

        std::ostringstream oss;
        oss << time;

        pqxx::result res = txn.exec_params(
            "INSERT INTO time_records (hours, minutes, seconds, formatted_time) "
            "VALUES ($1, $2, $3, $4) RETURNING id",
            time.toSeconds() / 3600,
            (time.toSeconds() % 3600) / 60,
            time.toSeconds() % 60,
            oss.str()
        );
        txn.commit();

        return res[0][0].as<int>();
        } catch (const std::exception& e) {
            std::cerr << "DB Error: " << e.what() << std::endl;
            throw;
        }
    }

    Time get(int id) const override {
        pqxx::connection conn(conn_str);
        pqxx::nontransaction txn(conn);

        pqxx::result res = txn.exec_params("SELECT formatted_time FROM time_records WHERE id = $1", id);

        if (res.empty()) {
            throw std::out_of_range("Time record not found in database.");
        }

        std::string timeStr = res[0][0].as<std::string>();
        return Time(timeStr);
    }

    bool exists(int id) const override {
        pqxx::connection conn(conn_str);
        pqxx::nontransaction txn(conn);
        pqxx::result res = txn.exec_params("SELECT 1 FROM time_records WHERE id = $1", id);
        return !res.empty();
    }
};

#include "../service/TimeService.h"
#include "httplib.h"
#include <iostream>
#include <sstream>

class TimeRestController {
private:
    TimeService& service;
    httplib::Server svr;

public:
    explicit TimeRestController(TimeService& srv) : service(srv) {
        setupRoutes();
    }

    void setupRoutes() {
        svr.Get(R"(/api/time/(\d+))", [&](const httplib::Request& req, httplib::Response& res) {
            int id = std::stoi(req.matches[1]);
            try {
                Time t = service.getRecord(id);
                std::ostringstream oss;
                oss << t;

                std::string json = R"({"id": )" + std::to_string(id) + R"(, "time": ")" + oss.str() + R"("})";
                res.set_content(json, "application/json");
            } catch (const std::out_of_range&) {
                res.status = 404;
                res.set_content(R"({"error": "Not found"})", "application/json");
            }
        });

        svr.Post("/api/time", [&](const httplib::Request& req, httplib::Response& res) {
            if (req.has_param("time_str")) {
            std::string timeStr = req.get_param_value("time_str");
            try {
                int newId = service.createTimeRecord(timeStr);

                res.status = 201;
                res.set_content(R"({"status": "success", "id": )" + std::to_string(newId) + "}", "application/json");
            } catch (const std::invalid_argument& e) {
                res.status = 400;
                res.set_content(std::string(R"({"error": ")") + e.what() + "\"}", "application/json");
            } catch (const std::exception& e) {
                res.status = 500;
                res.set_content(std::string(R"({"error": "Server error: )") + e.what() + "\"}", "application/json");
            }
        } else {
            res.status = 400;
            res.set_content(R"({"error": "Missing time_str parameter"})", "application/json");
        }
        });
    }

    void run(int port) {
        std::cout << "Time Microservice listening on 0.0.0.0:" << port << "...\n";
        svr.listen("0.0.0.0", port);
    }
};
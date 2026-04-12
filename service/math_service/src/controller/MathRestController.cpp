#include "MathRestController.h"
#include "iostream"

MathRestController::MathRestController(MathService& srv) : service(srv) {
    setupRoutes();
}

void MathRestController::setupRoutes() {
    svr.Get(R"(/api/math/ring)", [&](const httplib::Request& req, httplib::Response& res) {
        if (req.has_param("outer") && req.has_param("inner")) {
            try {
                double outer = std::stod(req.get_param_value("outer"));
                double inner = std::stod(req.get_param_value("inner"));
                double area = service.getRingArea(outer, inner);
                res.set_content(R"({"area": )" + std::to_string(area) + "}", "application/json");
            } catch (const std::exception& e) {
                res.status = 400;
                res.set_content(std::string(R"({"error": ")") + e.what() + "\"}", "application/json");
            }
        }
    });

    svr.Get(R"(/api/math/complex/add)", [&](const httplib::Request& req, httplib::Response& res) {
        if (req.has_param("re1") && req.has_param("im1") && req.has_param("re2") && req.has_param("im2")) {
            my_complex c1(std::stod(req.get_param_value("re1")), std::stod(req.get_param_value("im1")));
            my_complex c2(std::stod(req.get_param_value("re2")), std::stod(req.get_param_value("im2")));
            std::string result = service.addComplex(c1, c2);
            res.set_content(R"({"result": ")" + result + R"("})", "application/json");
        }
    });

    svr.Get(R"(/api/math/rational/add)", [&](const httplib::Request& req, httplib::Response& res){
        try {
            int num1 = std::stoi(req.get_param_value("num1"));
            int den1 = std::stoi(req.get_param_value("den1"));
            int num2 = std::stoi(req.get_param_value("num2"));
            int den2 = std::stoi(req.get_param_value("den2"));
            Rational r1(num1, den1);
            Rational r2(num2, den2);
            std::string result = service.addRationals(r1, r2);
            res.set_content(R"({"result": ")" + result + R"("})", "application/json");
        } catch (const std::exception& e) {
            res.status = 400;
            res.set_content(std::string(R"({"error": ")") + e.what() + "\"}", "application/json");
        }
    });

    svr.Get(R"(/api/math/triangle/area)", [&](const httplib::Request& req, httplib::Response& res) {
        try {
            double a = std::stod(req.get_param_value("a"));
            double b = std::stod(req.get_param_value("b"));
            double c = std::stod(req.get_param_value("c"));
            double area = service.getTriangleArea(a, b, c);
            res.set_content(R"({"area": )" + std::to_string(area) + "}", "application/json");
        } catch (const std::exception& e) {
            res.status = 400;
            res.set_content(std::string(R"({"error": ")") + e.what() + "\"}", "application/json");
        }
    });
}

void MathRestController::run(int port) {
    std::cout << "Math Microservice listening on 0.0.0.0:" << port << "...\n";
    svr.listen("0.0.0.0", port);
}

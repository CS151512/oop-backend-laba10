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

    svr.Get(R"(/api/math/complex/calc)", [&](const httplib::Request& req, httplib::Response& res) {
    if (req.has_param("re1") && req.has_param("im1") && req.has_param("re2") && req.has_param("im2") && req.has_param("op")) {
        try {
            my_complex c1(std::stod(req.get_param_value("re1")), std::stod(req.get_param_value("im1")));
            my_complex c2(std::stod(req.get_param_value("re2")), std::stod(req.get_param_value("im2")));
            std::string op = req.get_param_value("op");

            std::string result;
            if (op == "add") result = service.addComplex(c1, c2);
            else if (op == "sub") result = service.subComplex(c1, c2);
            else if (op == "mul") result = service.mulComplex(c1, c2);
            else if (op == "div") result = service.divComplex(c1, c2);
            else if (op == "eq") result = service.eqComplex(c1, c2);
            else if (op == "neq") result = service.neqComplex(c1, c2);
            else throw std::invalid_argument("Unknown operation");

            res.set_content(R"({"result": ")" + result + R"("})", "application/json");
        } catch (const std::exception& e) {
            res.status = 400;
            res.set_content(std::string(R"({"error": ")") + e.what() + "\"}", "application/json");
        }
    }
});

    svr.Get(R"(/api/math/rational/calc)", [&](const httplib::Request& req, httplib::Response& res){
        if (req.has_param("num1") && req.has_param("den1") && req.has_param("num2") && req.has_param("den2") && req.has_param("op")) {
            try {
                int num1 = std::stoi(req.get_param_value("num1"));
                int den1 = std::stoi(req.get_param_value("den1"));
                int num2 = std::stoi(req.get_param_value("num2"));
                int den2 = std::stoi(req.get_param_value("den2"));
                std::string op = req.get_param_value("op");

                Rational r1(num1, den1);
                Rational r2(num2, den2);

                std::string result;
                if (op == "add") result = service.addRationals(r1, r2);
                else if (op == "sub") result = service.subRationals(r1, r2);
                else if (op == "div") result = service.divRationals(r1, r2);
                else throw std::invalid_argument("Unknown operation");

                res.set_content(R"({"result": ")" + result + R"("})", "application/json");
            } catch (const std::exception& e) {
                res.status = 400;
                res.set_content(std::string(R"({"error": ")") + e.what() + "\"}", "application/json");
            }
        }
    });

    svr.Get(R"(/api/math/history)", [&](const httplib::Request& req, httplib::Response& res) {
        try {
            std::string historyJson = service.getHistory(10);
            res.set_content(historyJson, "application/json");
        } catch (const std::exception& e) {
            res.status = 500;
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

    svr.Get(R"(/api/math/complex/polar)", [&](const httplib::Request& req, httplib::Response& res) {
        if (req.has_param("re") && req.has_param("im")) {
            try {
                double re = std::stod(req.get_param_value("re"));
                double im = std::stod(req.get_param_value("im"));

                my_complex c(re, im);

                std::string result = service.toPolarComplex(c);

                res.set_content(R"({"result": ")" + result + R"("})", "application/json");
            } catch (const std::exception& e) {
                res.status = 400;
                res.set_content(std::string(R"({"error": ")") + e.what() + "\"}", "application/json");
            }
        }
    });

}

void MathRestController::run(int port) {
    std::cout << "Math Microservice listening on 0.0.0.0:" << port << "...\n";
    svr.listen("0.0.0.0", port);
}

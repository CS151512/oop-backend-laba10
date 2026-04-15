#include "MathService.h"
#include "../domain/Figures.h"
#include "../domain/Ring.h"

MathService::MathService(IMathRepository& repository) : repo(repository) {}

std::string MathService::addComplex(const my_complex& a, const my_complex& b) {
    my_complex res = a + b;
    std::string resStr = res.toString();
    std::string inputJson = R"({"op": "add_complex"})";
    repo.saveOperation("complex_addition", inputJson, resStr);
    return resStr;
}

std::string MathService::subComplex(const my_complex& a, const my_complex& b) {
    my_complex res = a - b;
    std::string resStr = res.toString();
    std::string inputJson = R"({"op": "sub_complex"})";
    repo.saveOperation("complex_subtraction", inputJson, resStr);
    return resStr;
}

std::string MathService::mulComplex(const my_complex& a, const my_complex& b) {
    my_complex res = a * b;
    std::string resStr = res.toString();
    std::string inputJson = R"({"op": "mul_complex"})";
    repo.saveOperation("complex_multiplication", inputJson, resStr);
    return resStr;
}

std::string MathService::divComplex(const my_complex& a, const my_complex& b) {
    my_complex res = a / b;
    std::string resStr = res.toString();
    repo.saveOperation("complex_division", R"({"op": "div"})", resStr);
    return resStr;
}

std::string MathService::eqComplex(const my_complex& a, const my_complex& b) {
    bool res = (a == b);
    std::string resStr = res ? "True" : "False";
    repo.saveOperation("complex_compare_eq", R"({"op": "eq"})", resStr);
    return resStr;
}

std::string MathService::neqComplex(const my_complex& a, const my_complex& b) {
    bool res = (a != b);
    std::string resStr = res ? "True" : "False";
    repo.saveOperation("complex_compare_neq", R"({"op": "neq"})", resStr);
    return resStr;
}

double MathService::getTriangleArea(double a, double b, double c) {
    triangle t(a, b, c);
    double area = t.area();
    std::string inputJson = R"({"a": )" + std::to_string(a) + R"(, "b": )" + std::to_string(b) + R"(, "c": )" + std::to_string(c) + "}";
    repo.saveOperation("triangle_area", inputJson, std::to_string(area));
    return area;
}

std::string MathService::addRationals(const Rational& r1, const Rational& r2) {
    Rational res = r1.add(r2);
    std::string resStr = res.toString();
    std::string inputJson = R"({"op": "add_rationals"})";
    repo.saveOperation("rational_addition", inputJson, resStr);
    return resStr;
}

double MathService::getRingArea(double outer, double inner) {
    double area = calculateRingArea(outer, inner);
    std::string inputJson = R"({"outer": )" + std::to_string(outer) + R"(, "inner": )" + std::to_string(inner) + "}";
    repo.saveOperation("ring_area", inputJson, std::to_string(area));
    return area;
}

std::string MathService::toPolarComplex(const my_complex& c) {
    std::string resStr = c.toPolar();

    std::string inputJson = R"({"re": )" + std::to_string(c.getRe()) +
                           R"(, "im": )" + std::to_string(c.getIm()) + "}";

    repo.saveOperation("complex_polar_conversion", inputJson, resStr);

    return resStr;
}
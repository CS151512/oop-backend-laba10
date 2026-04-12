#pragma once
#include "../repository/IMathRepository.h"
#include "../domain/Complex.h"
#include "../domain/Rational.h"
#include "string"

class MathService {
private:
    IMathRepository& repo;

public:
    explicit MathService(IMathRepository& repository);

    std::string addComplex(const my_complex& a, const my_complex& b);
    double getTriangleArea(double a, double b, double c);
    std::string addRationals(const Rational& r1, const Rational& r2);
    double getRingArea(double outer, double inner);
};
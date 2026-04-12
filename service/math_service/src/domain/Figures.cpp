#include "Figures.h"
#include "cmath"
#include "stdexcept"

figure::figure(double a, double b) : x(a), y(b) {}

double figure::area() const {
    return 0;
}

triangle::triangle(double a, double b, double c) : figure(a, b), z(c) {
    if (a + b <= c || a + c <= b || b + c <= a) {
        throw std::invalid_argument("Invalid triangle sides");
    }
}

double triangle::area() const {
    double p = (x + y + z) / 2.0;
    return std::sqrt(p * (p - x) * (p - y) * (p - z));
}
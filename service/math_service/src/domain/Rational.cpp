#include "Rational.h"
#include "stdexcept"
#include "numeric"

void Rational::simplify() {
    int gcd = std::gcd(a, b);
    a /= gcd;
    b /= gcd;

    if (b < 0) {
        a = -a;
        b = -b;
    }
}

Pair::Pair(int first, int second) : a(first), b(second) {}

bool Pair::operator==(const Pair& other) const {
    return a == other.a && b == other.b;
}

int Pair::multiply() const {
    return a * b;
}

Pair Pair::subtract(const Pair& other) const {
    return Pair(a - other.a, b - other.b);
}

int Pair::getFirst() const { return a; }
int Pair::getSecond() const { return b; }

Rational::Rational(int first, int second) : Pair(first, second) {
    if (b == 0) {
        throw std::invalid_argument("Denominator cannot be zero");
    }
    simplify();
}

Rational Rational::add(const Rational& other) const {
    int new_a = a * other.b + other.a * b;
    int new_b = b * other.b;
    return Rational(new_a, new_b);
}

Rational Rational::divide(const Rational& other) const {
    if (other.a == 0) throw std::invalid_argument("Division by zero");
    return Rational(a * other.b, b * other.a);
}

Pair Rational::subtract(const Pair& other) const {
    return Pair(-(a * other.getSecond() - other.getFirst() * b), b * other.getSecond());
}

std::string Rational::toString() const {
    if (b == 1) {
        return std::to_string(a);
    }
    return std::to_string(a) + "/" + std::to_string(b);
}
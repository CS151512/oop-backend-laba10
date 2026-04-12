#pragma once
#include "string"
#include "iostream"

class my_complex {
    double Re, Im;

public:
    my_complex(double a = 0, double b = 0);
    my_complex(const my_complex& X);
    ~my_complex() = default;

    void setRe(double x);
    void setIm(double x);
    double getRe() const;
    double getIm() const;

    double mod() const;
    std::string toPolar() const;
    std::string toString() const;

    my_complex& operator=(const my_complex& A);

    friend my_complex operator+(const my_complex& A, const my_complex& B);
    friend my_complex operator-(const my_complex& A, const my_complex& B);
    friend my_complex operator*(const my_complex& A, const my_complex& B);
    friend my_complex operator/(const my_complex& A, const my_complex& B);
    friend bool operator==(const my_complex& A, const my_complex& B);
    friend bool operator!=(const my_complex& A, const my_complex& B);
    friend std::ostream& operator<<(std::ostream& out, const my_complex& X);
};
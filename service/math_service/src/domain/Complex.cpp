#include "Complex.h"
#include "cmath"
#include "sstream"

#define EPS 0.000000001

my_complex::my_complex(double a, double b) : Re(a), Im(b) {}

my_complex::my_complex(const my_complex& X) : Re(X.Re), Im(X.Im) {}

void my_complex::setRe(double x) { Re = x; }
void my_complex::setIm(double x) { Im = x; }
double my_complex::getRe() const { return Re; }
double my_complex::getIm() const { return Im; }

double my_complex::mod() const {
    return std::sqrt(Re * Re + Im * Im);
}

std::string my_complex::toPolar() const {
    double r = mod();
    double theta = std::atan2(Im, Re);
    std::ostringstream ss;
    ss << r << " * (cos(" << theta << ") + i*sin(" << theta << "))";
    return ss.str();
}

std::string my_complex::toString() const {
    std::ostringstream ss;
    if (std::abs(Im) < EPS) {
        ss << Re;
    } else if (Im > 0) {
        ss << Re << "+" << Im << "i";
    } else {
        ss << Re << Im << "i";
    }
    return ss.str();
}

my_complex& my_complex::operator=(const my_complex& A) {
    if (&A != this) {
        Re = A.Re;
        Im = A.Im;
    }
    return *this;
}

my_complex operator+(const my_complex& A, const my_complex& B) {
    return my_complex(A.Re + B.Re, A.Im + B.Im);
}

my_complex operator-(const my_complex& A, const my_complex& B) {
    return my_complex(A.Re - B.Re, A.Im - B.Im);
}

my_complex operator*(const my_complex& A, const my_complex& B) {
    return my_complex(A.Re * B.Re - A.Im * B.Im, A.Re * B.Im + A.Im * B.Re);
}

my_complex operator/(const my_complex& A, const my_complex& B) {
    double denominator = B.Re * B.Re + B.Im * B.Im;
    if (denominator < EPS) throw std::invalid_argument("Division by zero");
    return my_complex((A.Re * B.Re + A.Im * B.Im) / denominator,
                      (A.Im * B.Re - A.Re * B.Im) / denominator);
}

bool operator==(const my_complex& A, const my_complex& B) {
    return std::abs(A.Re - B.Re) < EPS && std::abs(A.Im - B.Im) < EPS;
}

bool operator!=(const my_complex& A, const my_complex& B) {
    return !(A == B);
}

std::ostream& operator<<(std::ostream& out, const my_complex& X) {
    out << X.toString();
    return out;
}

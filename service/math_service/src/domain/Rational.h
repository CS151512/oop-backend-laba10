#pragma once
#include "string"

class Pair {
protected:
    int a, b;
public:
    Pair(int first, int second);
    virtual ~Pair() = default;

    bool operator==(const Pair& other) const;
    int multiply() const;
    virtual Pair subtract(const Pair& other) const;

    int getFirst() const;
    int getSecond() const;
};

class Rational : public Pair {
private:
    void simplify();
public:
    Rational(int first, int second);

    Rational add(const Rational& other) const;
    Rational divide(const Rational& other) const;
    Pair subtract(const Pair& other) const override;

    std::string toString() const;
};
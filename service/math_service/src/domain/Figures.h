#pragma once

class figure {
protected:
    double x, y;
public:
    figure(double a = 0, double b = 0);
    virtual double area() const;
    virtual ~figure() = default;
};

class triangle : public figure {
private:
    double z;
public:
    triangle(double a, double b, double c);
    double area() const override;
};
#pragma once
#include "stdexcept"
#include "string"

class RingGeometryException : public std::invalid_argument {
public:
    explicit RingGeometryException(const std::string& message);
};

double calculateRingArea(double outerRadius, double innerRadius);
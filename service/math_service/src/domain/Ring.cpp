#include "Ring.h"
#include "cmath"

RingGeometryException::RingGeometryException(const std::string& message)
    : std::invalid_argument(message) {}

double calculateRingArea(double outerRadius, double innerRadius) {
    if (outerRadius < 0 || innerRadius < 0) {
        throw RingGeometryException("Radii cannot be negative");
    }
    if (innerRadius >= outerRadius) {
        throw RingGeometryException("Inner radius must be strictly less than outer radius");
    }
    return M_PI * (outerRadius * outerRadius - innerRadius * innerRadius);
}
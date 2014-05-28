#ifndef FLOATING_POINT_COMPARER_H
#define FLOATING_POINT_COMPARER_H

#include "Comparer.hpp"


// Executes basic comparisons over floating point numbers using a specified precision range.
class FloatingPointComparer : public Comparer<double> {
private:

    double precision;

public:

    FloatingPointComparer() {
        FloatingPointComparer(0.000001); // Default precision
    }

    FloatingPointComparer(double precision) {
        this->precision = precision;
    }

    // Gets the precision used to compare floating point numbers
    double getPrecision() {
        return precision;
    }

    void setPrecision(double precision) {
        this->precision = precision;
    }

    // Compare two floating point numbers a and b, returning:
    //
    //      0  if a == b within the precision range
    //     +1  if a > b
    //     -1  if a < b
    //
    int compare(double a, double b);
};

#endif

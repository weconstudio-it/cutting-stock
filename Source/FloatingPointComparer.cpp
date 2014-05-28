#include "FloatingPointComparer.hpp"

#include <math.h>


int FloatingPointComparer::compare(double a, double b) {
    double difference = (a - b);

    double delta = fabs(difference);
    if (delta <= precision)
        return 0; // equals
    else {
        if (difference > 0)
            return +1;
        else if (difference < 0)
            return -1;
        else
            return 0;
    }
}

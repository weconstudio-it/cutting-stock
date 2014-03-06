#ifndef INTEGER_COMPARER_H
#define INTEGER_COMPARER_H

#include "Comparer.hpp"


// Concrete implementation of a comparer for integer numbers.
class IntegerComparer : public Comparer<int> {

public:

    // Compare two integer numbers a and b, returning:
    //
    //      0  if a == b
    //     +1  if a > b
    //     -1  if a < b
    //
    int compare(int a, int b) {
        if (a < b)
            return -1;
        else if (a > b)
            return +1;
        else
            return 0;
    }

    bool equals(int a, int b) {
        return a == b;
    }
};

#endif

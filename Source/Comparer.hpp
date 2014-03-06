#ifndef COMPARER_H
#define COMPARER_H


// Defines an abstract interface for a generic type comparer.
template <typename T> class Comparer {

public:

    // Pure virtual method.
    // Compares two values a and b, returning:
    //
    //      0  if a == b
    //     +1  if a > b
    //     -1  if a < b
    //
    virtual int compare(T a, T b) = 0;

    // Determines if two values are equal.
    virtual bool equals(T a, T b) {
        return compare(a, b) == 0;
    }

    // Gets the maximum value between values a and b.
    virtual T max(T a, T b) {
        if (compare(a, b) >= 0)
            return a;
        else
            return b;
    }

    // Gets the minimum value between values a and b.
    virtual T min(T a, T b) {
        if (compare(a, b) <= 0)
            return a;
        else
            return b;
    }
};

#endif

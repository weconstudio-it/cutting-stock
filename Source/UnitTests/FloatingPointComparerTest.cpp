#include "FloatingPointComparerTest.hpp"

#include <assert.h>
#include <iostream>
using namespace std;

#include "../FloatingPointComparer.hpp"
#include "../IntegerComparer.hpp"


void testFloatingPointComparer()
{
    FloatingPointComparer comparer(0.0001);

    assert(comparer.compare(0.002, 0.003) < 0);
    assert(not comparer.equals(0.002, 0.003));

    assert(comparer.compare(0.003, 0.002) > 0);
    assert(not comparer.equals(0.003, 0.002));

    assert(comparer.compare(0.01, 0.01) == 0);
    assert(comparer.equals(0.01, 0.01));

    //
    // Beyond precision
    //

    assert(comparer.compare(0.0002, 0.0003) == 0);
    assert(comparer.equals(0.0002, 0.0003));

    assert(comparer.compare(0.00002, 0.00003) == 0);
    assert(comparer.equals(0.00002, 0.00003));
}

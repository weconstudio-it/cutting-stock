#include "CuttingStockPatternTest.hpp"

#include <assert.h>

#include "../CuttingStockPattern.hpp"


void testCuttingStockPattern() {
    CuttingStockPattern pattern;

    pattern.addCut(5, 2);
    pattern.addCut(3, 7);
    pattern.addCut(2, 6);
    pattern.addCut(7, 0); // won't define cuts with 0 pieces

    assert(pattern.getPieces(5) == 2);
    assert(pattern.getPieces(3) == 7);
    assert(pattern.getPieces(2) == 6);
    assert(pattern.getPieces(7) == 0); // not defined
    assert(pattern.getPieces(9) == 0); // not defined

    assert(pattern.getCutsCount() == 3);
}

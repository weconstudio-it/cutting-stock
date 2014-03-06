#include "CuttingStockInstanceTest.hpp"

#include <assert.h>

#include "../CuttingStockInstance.hpp"


void testCuttingStockInstance() {

    CuttingStockInstance instance;

    instance.addRequirement(5, 3);
    instance.addRequirement(2, 4);
    instance.addRequirement(1, 3);
    instance.addRequirement(8, 10);
    instance.addRequirement(9, 0);
    instance.addRequirement(6, 2);
    instance.setBarWidth(10);


    assert(instance.getBarWidth() == 10);

    assert(instance.getRequirementCount() == 6);
    assert(instance.getPieces(5) == 3);
    assert(instance.getPieces(2) == 4);
    assert(instance.getPieces(1) == 3);
    assert(instance.getPieces(6) == 2);
    assert(instance.getPieces(9) == 0);
    assert(instance.getPieces(8) == 10);

    assert(not instance.hasRequirement(0));
    assert(not instance.hasRequirement(3));
    assert(not instance.hasRequirement(4));
    assert(not instance.hasRequirement(7));
    assert(not instance.hasRequirement(10));
}

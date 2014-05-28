#include "CuttingStockInstanceBuilderTest.hpp"

#include <assert.h>
#include <sstream>

#include "../CuttingStockInstance.hpp"
#include "../CuttingStockInstanceBuilder.hpp"

using namespace std;

void testCuttingStockInstanceBuilder()
{
    CuttingStockInstanceBuilder builder;

    stringstream input (stringstream::in | stringstream::out);
    input << "10" << endl; // the fixed bar width
    input << "5" << endl; // the number of requirements
    // the requirements:
    input << "3" << " " << "4" << endl;
    input << "4" << " " << "3" << endl;
    input << "5" << " " << "3" << endl;
    input << "6" << " " << "1" << endl;
    input << "7" << " " << "1" << endl;
    input << "99" << " " << "100" << endl;
    input.seekg(0, ios::beg);

    CuttingStockInstance* instance = builder.parseStream(input);

    assert(instance->getBarWidth() == 10);

    assert(instance->getRequirementCount() == 5);
    assert(instance->getPieces(3) == 4);
    assert(instance->getPieces(4) == 3);
    assert(instance->getPieces(5) == 3);
    assert(instance->getPieces(6) == 1);
    assert(instance->getPieces(7) == 1);

    // 99 should not be inside the map
    assert(not instance->hasRequirement(99));

    assert(not instance->hasRequirement(0));
    assert(not instance->hasRequirement(1));
    assert(not instance->hasRequirement(2));

    delete instance;
}

#include "CuttingStockInstanceBuilder.hpp"

#include <istream>
using namespace std;


CuttingStockInstance* CuttingStockInstanceBuilder::parseStream(istream& input)
{
    CuttingStockInstance* instance = new CuttingStockInstance();

    int barWidth, numberOfRequirements;

    // The fixed bar width
    input >> barWidth;
    // the number of requirements M, such that i={1 .. M}, i is the requirement index
    input >> numberOfRequirements;

    instance->setBarWidth(barWidth);

    // Read the requirements i
    for (int i = 0; i < numberOfRequirements; i++) {
        int width;
        int pieces;
        input >> width >> pieces;

        // Requirement (w[i], p[i]), where w[i] is the width of requirement i, p[i] is
        // the number of pieces to be produced for width w[i].
        instance->addRequirement(width, pieces);
    }

    return instance;
}

#ifndef CUTTING_STOCK_INSTANCE_BUILDER_H
#define CUTTING_STOCK_INSTANCE_BUILDER_H

#include <istream>
#include "CuttingStockInstance.hpp"


// Builds a cutting stock instance.
class CuttingStockInstanceBuilder
{

public:

    // Parses an input stream, building a cutting-stock problem instance.
    // The stream should be text-based, adhering to the following format:
    //
    //  first line: fixed width W
    //	second line: number of requirements M, such that i = {1 .. M}
    //  remaining lines:
    //      first column: w[i], the width of the requirement i
    //      second column: p[i], the number of pieces of width w[i] that should be produced
    //          for requirement i
    //
    CuttingStockInstance* parseStream(std::istream& input);
};

#endif

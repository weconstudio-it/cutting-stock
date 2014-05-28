#ifndef CUTTING_STOCK_MATHPROG_INSTANCE_H
#define CUTTING_STOCK_MATHPROG_INSTANCE_H

#include "CuttingStockInstance.hpp"

#include <ostream>


class CuttingStockMathProgInstance : public CuttingStockInstance
{

public:

    CuttingStockMathProgInstance(CuttingStockInstance& instance)
    {
        // Copies the data from the provided instance.

        for (int i = 1; i <= instance.getRequirementCount(); i++) {
            int width = instance.getWidth(i);
            int pieces = instance.getPieces(width);
            addRequirement(width, pieces);
        }

        setBarWidth(instance.getBarWidth());
    }

    // Writes MathProg formatted data representing this instance to an output stream.
    // The stream is not closed neither flushed.
    void write(std::ostream& output);
};

#endif

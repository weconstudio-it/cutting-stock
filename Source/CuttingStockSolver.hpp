#ifndef CUTTING_STOCK_SOLVER_H
#define CUTTING_STOCK_SOLVER_H

#include <deque>
#include <map>
#include <stdexcept>
#include <assert.h>

#include "CuttingStockPattern.hpp"
#include "CuttingStockInstance.hpp"

// Represents an abstract pattern generation based solution for the cutting-stock problem.
template <typename AllocationType>
class CuttingStockSolution {

private:

    // The array of cutting patterns. All indexes are 1-based.
    std::deque<CuttingStockPattern*> patterns;

    // Associative map between pattern indexes and their allocations.
    std::map<unsigned, AllocationType> allocations;

    // The summation of all pattern allocations (objective function value)
    AllocationType totalAllocation;

public:

   // Constructor
    CuttingStockSolution() { }

    // Destructor
    ~CuttingStockSolution() {
        for (unsigned i = 0; i < patterns.size(); i++)
            delete patterns.at(i);
    }

    // Adds a cutting pattern to the list.
    void addPattern(CuttingStockPattern* pattern) {
        patterns.push_back(pattern);
    }

    // Retrieves a cutting pattern with the given index from the list.
    // All indexes are 1-based.
    CuttingStockPattern* getPattern(unsigned index) {
        assert(index > 0);
        return patterns.at(index - 1);
    }

    // Gets the number of patterns currently in the list.
    int getPatternCount() {
        return patterns.size();
    }

    // Defines the allocation of an existing cutting pattern index. All indexes are 1-based.
    void setAllocation(unsigned patternIndex, AllocationType allocation) {
        assert(patternIndex > 0);
        if (patternIndex > patterns.size())
            throw std::out_of_range("Invalid pattern index.");

        allocations.insert(
            std::pair<unsigned, AllocationType>(patternIndex, allocation));
    }

    // Gets the allocation of a given cutting pattern index. If the allocation is not defined,
    // throws an exception.
    AllocationType getAllocation(unsigned patternIndex) {
        typename std::map<unsigned, AllocationType>::iterator it;
        it = allocations.find(patternIndex);
        if (it != allocations.end())
            return it->second;
        else
            throw std::out_of_range("Pattern allocation not defined.");
    }

    // Gets the summation of all pattern allocations.
    AllocationType getTotalAllocation() {
        return totalAllocation;
    }

    // Sets the summation of all pattern allocations.
    void setTotalAllocation(AllocationType totalAllocation) {
        this->totalAllocation = totalAllocation;
    }

    // Gets the total pieces of a given width produced by all patterns and their
    // respective allocations defined by this instance.
    AllocationType getProducedPieces(int width) {
        AllocationType producedPieces = 0;
        for (int j = 1; j <= getPatternCount(); j++) {
            CuttingStockPattern* pattern = getPattern(j);
            producedPieces += (AllocationType) pattern->getPieces(width) * getAllocation(j);
        }
        return producedPieces;
    }
};


// Abstract pattern generation based cutting stock solver
template <typename AllocationType>
class CuttingStockSolver
{
public:

    virtual CuttingStockSolution<AllocationType>* solve(CuttingStockInstance* instance) = 0;

};


#endif

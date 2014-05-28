#include "CuttingStockSolutionTest.hpp"

#include "../CuttingStockSolver.hpp"


void testCuttingStockSolution()
{
    CuttingStockSolution<double> solution;

    CuttingStockPattern* pattern;

    pattern = new CuttingStockPattern();
    pattern->addCut(5, 3);
    pattern->addCut(2, 1);
    solution.addPattern(pattern);
    solution.setAllocation(1, 3.25);

    pattern = new CuttingStockPattern();
    pattern->addCut(1, 5);
    pattern->addCut(2, 3);
    pattern->addCut(4, 2);
    solution.addPattern(pattern);
    solution.setAllocation(2, 0.75);

    pattern = new CuttingStockPattern();
    pattern->addCut(3, 4);
    pattern->addCut(1, 3);
    solution.addPattern(pattern);
    solution.setAllocation(3, 2);

    pattern = new CuttingStockPattern();
    pattern->addCut(4, 10);
    pattern->addCut(5, 1);
    solution.addPattern(pattern);
    solution.setAllocation(4, 5.7525);


    assert(solution.getPatternCount() == 4);

    pattern = solution.getPattern(1);
    assert(pattern->getCutsCount() == 2);
    assert(pattern->getPieces(5) == 3);
    assert(pattern->getPieces(2) == 1);
    assert(solution.getAllocation(1) == 3.25);

    pattern = solution.getPattern(2);
    assert(pattern->getCutsCount() == 3);
    assert(pattern->getPieces(1) == 5);
    assert(pattern->getPieces(2) == 3);
    assert(pattern->getPieces(4) == 2);
    assert(solution.getAllocation(2) == 0.75);

    pattern = solution.getPattern(3);
    assert(pattern->getCutsCount() == 2);
    assert(pattern->getPieces(3) == 4);
    assert(pattern->getPieces(1) == 3);
    assert(solution.getAllocation(3) == 2);

    pattern = solution.getPattern(4);
    assert(pattern->getCutsCount() == 2);
    assert(pattern->getPieces(4) == 10);
    assert(pattern->getPieces(5) == 1);
    assert(solution.getAllocation(4) == 5.7525);
}

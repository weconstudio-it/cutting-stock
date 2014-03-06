#include "CuttingStockLinearRelaxationSolverTest.hpp"

#include <assert.h>
#include <iostream>
using namespace std;

#include "../CuttingStockInstance.hpp"
#include "../CuttingStockLinearRelaxationSolver.hpp"
#include "../FloatingPointComparer.hpp"

using namespace std;


void testSolver1()
{
    CuttingStockLinearRelaxationSolver solver;

    // Tests using a very tiny instance, which defines a bar of size 3 and widths 1, 2 and 3.
    CuttingStockInstance* instance = new CuttingStockInstance();
    instance->setBarWidth(3);
    instance->addRequirement(1, 4);
    instance->addRequirement(2, 13);
    instance->addRequirement(3, 7);

    CuttingStockSolution<double>* solution = solver.solve(instance);

    assert(solution->getPatternCount() == 5);

    CuttingStockPattern* pattern;

    //
    // First three patterns are the initial feasible columns
    //

    // 1 piece of width 1
    pattern = solution->getPattern(1);
    assert(pattern->getCutsCount() == 1);
    assert(pattern->getPieces(1) == 1);

    // 1 piece of width 2
    pattern = solution->getPattern(2);
    assert(pattern->getCutsCount() == 1);
    assert(pattern->getPieces(2) == 1);

    // 1 piece of width 3
    pattern = solution->getPattern(3);
    assert(pattern->getCutsCount() == 1);
    assert(pattern->getPieces(3) == 1);

    // 3 pieces of width 1
    pattern = solution->getPattern(4);
    assert(pattern->getCutsCount() == 1);
    assert(pattern->getPieces(1) == 3);

    // 1 piece of width 1 + 1 piece of width 2
    pattern = solution->getPattern(5);
    assert(pattern->getCutsCount() == 2);
    assert(pattern->getPieces(1) == 1);
    assert(pattern->getPieces(2) == 1);


    // Verifies if all pieces produced by the solution satisfy the requirements.
    FloatingPointComparer comparer(0.000000001);
    for (int i = 1; i <= instance->getRequirementCount(); i++) {
        assert(comparer.equals(
            solution->getProducedPieces(i), instance->getPieces(i)));
    }

    // Clean-up
    delete instance;
    delete solution;
}

void testSolver2()
{
    CuttingStockLinearRelaxationSolver solver;

    // Tests using a very tiny instance, which defines a bar of size 4 and widths 1, 2, 3 and 4.
    CuttingStockInstance* instance = new CuttingStockInstance();
    instance->setBarWidth(4);
    instance->addRequirement(1, 7);
    instance->addRequirement(2, 8);
    instance->addRequirement(3, 3);
    instance->addRequirement(4, 11);

    CuttingStockSolution<double>* solution = solver.solve(instance);

    assert(solution->getPatternCount() == 7);

    CuttingStockPattern* pattern;

    //
    // First four patterns are the initial feasible columns
    //

    // 1 piece of width 1
    pattern = solution->getPattern(1);
    assert(pattern->getCutsCount() == 1);
    assert(pattern->getPieces(1) == 1);

    // 1 piece of width 2
    pattern = solution->getPattern(2);
    assert(pattern->getCutsCount() == 1);
    assert(pattern->getPieces(2) == 1);

    // 1 piece of width 3
    pattern = solution->getPattern(3);
    assert(pattern->getCutsCount() == 1);
    assert(pattern->getPieces(3) == 1);

    // 1 piece of width 4
    pattern = solution->getPattern(4);
    assert(pattern->getCutsCount() == 1);
    assert(pattern->getPieces(4) == 1);

    // 4 pieces of width 1
    pattern = solution->getPattern(5);
    assert(pattern->getCutsCount() == 1);
    assert(pattern->getPieces(1) == 4);

    // 2 pieces of width 2
    pattern = solution->getPattern(6);
    assert(pattern->getCutsCount() == 1);
    assert(pattern->getPieces(2) == 2);


    // 1 piece of width 3 + 1 piece of width 1
    pattern = solution->getPattern(7);
    assert(pattern->getCutsCount() == 2);
    assert(pattern->getPieces(3) == 1);
    assert(pattern->getPieces(1) == 1);


    // Verifies if all pieces produced by the solution satisfy the requirements.
    FloatingPointComparer comparer(0.000000001);
    for (int i = 1; i <= instance->getRequirementCount(); i++) {
        assert(comparer.equals(
            solution->getProducedPieces(i), instance->getPieces(i)));
    }

    // Clean-up
    delete instance;
    delete solution;
}

void testCuttingStockLinearRelaxationSolver() {
    testSolver1();
    testSolver2();
}

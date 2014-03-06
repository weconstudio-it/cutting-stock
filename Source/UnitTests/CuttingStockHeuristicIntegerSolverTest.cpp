#include "CuttingStockHeuristicIntegerSolverTest.hpp"

#include "../CuttingStockInstance.hpp"
#include "../CuttingStockHeuristicIntegerSolver.hpp"


void test1() {
    CuttingStockHeuristicIntegerSolver solver;

    CuttingStockInstance* instance = new CuttingStockInstance();
    instance->setBarWidth(4);
    instance->addRequirement(1, 7);
    instance->addRequirement(2, 8);
    instance->addRequirement(3, 3);
    instance->addRequirement(4, 11);

    CuttingStockSolution<int>* solution = solver.solve(instance);

    assert(solution->getProducedPieces(1) >= 7);
    assert(solution->getProducedPieces(2) >= 8);
    assert(solution->getProducedPieces(3) >= 3);
    assert(solution->getProducedPieces(4) >= 11);

    delete instance;
    delete solution;
}

void test2() {
    CuttingStockHeuristicIntegerSolver solver;

    CuttingStockInstance* instance = new CuttingStockInstance();
    instance->setBarWidth(10);
    instance->addRequirement(1, 110);
    instance->addRequirement(2, 77);
    instance->addRequirement(3, 89);
    instance->addRequirement(4, 35);
    instance->addRequirement(5, 112);

    CuttingStockSolution<int>* solution = solver.solve(instance);

    assert(solution->getProducedPieces(1) >= 110);
    assert(solution->getProducedPieces(2) >= 77);
    assert(solution->getProducedPieces(3) >= 89);
    assert(solution->getProducedPieces(4) >= 35);
    assert(solution->getProducedPieces(5) >= 112);

    delete instance;
    delete solution;
}

void testCuttingStockHeuristicIntegerSolver() {
    test1();
    test2();
}

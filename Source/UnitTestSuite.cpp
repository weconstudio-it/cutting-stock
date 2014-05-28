#include "UnitTests/CuttingStockInstanceTest.hpp"
#include "UnitTests/CuttingStockPatternTest.hpp"
#include "UnitTests/CuttingStockSolutionTest.hpp"
#include "UnitTests/CuttingStockInstanceBuilderTest.hpp"
#include "UnitTests/CuttingStockLinearRelaxationSolverTest.hpp"
#include "UnitTests/CuttingStockHeuristicIntegerSolverTest.hpp"
#include "UnitTests/IntegerKnapsackSolverTest.hpp"
#include "UnitTests/FloatingPointComparerTest.hpp"

#include <iostream>
using namespace std;

void printTestName(string name) {
    cout << "\t- " << name << endl << endl;
}


int main(int argc, char *argv[])
{

    cout << "Running Unit Test Suite..." << endl << endl;

    printTestName("FloatingPointComparerTest");
    testFloatingPointComparer();

    printTestName("IntegerKnapsackSolverTest");
    testIntegerKnapsackSolver();

    printTestName("CuttingStockInstanceTest");
    testCuttingStockInstance();

    printTestName("CuttingStockInstanceBuilderTest");
    testCuttingStockInstanceBuilder();

    printTestName("CuttingStockPatternTest");
    testCuttingStockPattern();

    printTestName("CuttingStockSolutionTest");
    testCuttingStockSolution();

    printTestName("CuttingStockLinearRelaxationSolverTest");
    testCuttingStockLinearRelaxationSolver();

    printTestName("CuttingStockHeuristicIntegerSolverTest");
    testCuttingStockHeuristicIntegerSolver();

    cout << "All Tests PASSED." << endl;
    return 0;
}

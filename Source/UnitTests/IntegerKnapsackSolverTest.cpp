#include "IntegerKnapsackSolverTest.hpp"

#include <assert.h>
#include <iostream>
using namespace std;

#include "../IntegerKnapsackSolver.hpp"
#include "../FloatingPointComparer.hpp"
#include "../IntegerComparer.hpp"


void testIntegerKnapsackInstance1() {

    //
    // max  7 x[1] + 9 x[2] + 2 x[3] + 15 x[4]
    //
    // s.t. 3 x[1] + 4 x[2] + x[3] + 7 x[4] ≤ 10,
    //
    //      x ∈ Z^4, x ≥ 0.
    //

    IntegerKnapsackInstance<int>* instance = new IntegerKnapsackInstance<int>();
    instance->setCapacity(10);
    instance->addItem(1, 7, 3);  // x[1]
    instance->addItem(2, 9, 4);  // x[2]
    instance->addItem(3, 2, 1);  // x[3]
    instance->addItem(4, 15, 7); // x[4]

    IntegerComparer* comparer = new IntegerComparer();
    IntegerKnapsackSolver<int> solver(comparer);
    IntegerKnapsackSolution<int>* solution = solver.solve(instance);

    assert(solution->getOptimalValue() == 23);
    assert(solution->getItemAmount(1) == 2);
    assert(solution->getItemAmount(2) == 1);
    assert(solution->getItemAmount(3) == 0);
    assert(solution->getItemAmount(4) == 0);

    // Clean-up
    delete instance;
    delete solution;
    delete comparer;
}


void testIntegerKnapsackInstance2() {

    //
    // max  11 x[1] + 7 x[2] + 5 x[3]
    //
    // s.t. x[1] + 2 x[2] + x[3] ≤ 5,
    //
    //      x ∈ Z^3, x ≥ 0.
    //

    IntegerKnapsackInstance<int>* instance = new IntegerKnapsackInstance<int>();
    instance->setCapacity(5);
    instance->addItem(1, 11, 1); // x[1]
    instance->addItem(2, 7, 2);  // x[2]
    instance->addItem(3, 5, 1);  // x[3]

    IntegerComparer* comparer = new IntegerComparer();
    IntegerKnapsackSolver<int> solver(comparer);
    IntegerKnapsackSolution<int>* solution = solver.solve(instance);

    assert(solution->getOptimalValue() == 55);
    assert(solution->getItemAmount(1) == 5);
    assert(solution->getItemAmount(2) == 0);
    assert(solution->getItemAmount(3) == 0);

    // Clean-up
    delete instance;
    delete solution;
    delete comparer;
}


// Test using floating point values
void testIntegerKnapsackInstance3() {

    //
    // max  11.5 x[1] + 7.9 x[2] + 5.2 x[3]
    //
    // s.t. 2 x[1] + 2 x[2] + x[3] ≤ 5,
    //
    //      x ∈ Z^3, x ≥ 0.
    //

    IntegerKnapsackInstance<double>* instance = new IntegerKnapsackInstance<double>();
    instance->setCapacity(5);
    instance->addItem(1, 11.5, 2); // x[1]
    instance->addItem(2, 7.9, 2);  // x[2]
    instance->addItem(3, 5.2, 1);  // x[3]

    FloatingPointComparer* comparer = new FloatingPointComparer();
    IntegerKnapsackSolver<double> solver(comparer);
    IntegerKnapsackSolution<double>* solution = solver.solve(instance);

    assert(solution->getOptimalValue() == (2.0*11.5 + 1.0*5.2));
    assert(comparer->equals(solution->getOptimalValue(), (2.0*11.5 + 1.0*5.2)));
    assert(solution->getItemAmount(1) == 2);
    assert(solution->getItemAmount(2) == 0);
    assert(solution->getItemAmount(3) == 1);

    // Clean-up
    delete instance;
    delete comparer;
    delete solution;
}


// Test using integer values as doubles
void testIntegerKnapsackInstance4() {

    //
    // max  7 x[1] + 9 x[2] + 2 x[3] + 15 x[4]
    //
    // s.t. 3 x[1] + 4 x[2] + x[3] + 7 x[4] ≤ 10,
    //
    //      x ∈ Z^4, x ≥ 0.
    //

    IntegerKnapsackInstance<double>* instance = new IntegerKnapsackInstance<double>();
    instance->setCapacity(10);
    instance->addItem(1, 7, 3);  // x[1]
    instance->addItem(2, 9, 4);  // x[2]
    instance->addItem(3, 2, 1);  // x[3]
    instance->addItem(4, 15, 7); // x[4]

    FloatingPointComparer* comparer = new FloatingPointComparer();
    IntegerKnapsackSolver<double> solver(comparer);
    IntegerKnapsackSolution<double>* solution = solver.solve(instance);

    assert(comparer->equals(solution->getOptimalValue(), 23));
    assert(solution->getItemAmount(1) == 2);
    assert(solution->getItemAmount(2) == 1);
    assert(solution->getItemAmount(3) == 0);
    assert(solution->getItemAmount(4) == 0);

    // Clean-up
    delete instance;
    delete solution;
    delete comparer;
}


void testIntegerKnapsackSolver() {
    testIntegerKnapsackInstance1();
    testIntegerKnapsackInstance2();
    testIntegerKnapsackInstance3();
    testIntegerKnapsackInstance4();
}

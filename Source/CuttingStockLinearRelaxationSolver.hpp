#ifndef CUTTING_STOCK_LINEAR_RELAXATION_SOLVER_H
#define CUTTING_STOCK_LINEAR_RELAXATION_SOLVER_H

#include <assert.h>
#include <deque>
#include <map>
#include <stdexcept>

#include "CuttingStockInstance.hpp"
#include "CuttingStockSolver.hpp"

#include "IntegerKnapsackSolver.hpp"
#include "FloatingPointComparer.hpp"


// Default precision used for floating-point number comparisons
#define CUTTING_STOCK_LINEAR_RELAXATION_DEFAULT_PRECISION 0.000001


// Stores runtime statistics from an execution of the pattern generation cutting-stock solver.
class CuttingStockLinearRelaxationSolverRuntimeStatistics
{
private:

    long totalExecutionTime;
    long subproblemAverageExecutionTime;

public:

    CuttingStockLinearRelaxationSolverRuntimeStatistics() {
        totalExecutionTime = 0;
        subproblemAverageExecutionTime = 0;
    }

    // Gets the total execution time, in microseconds.
    long getTotalExecutionTime() {
        return totalExecutionTime;
    }

    // Sets the total execution time, in microseconds.
    void setTotalExecutionTime(long t) {
        totalExecutionTime = t;
    }

    // Gets the average execution time of the pattern generation subproblem's solution,
    // in microseconds.
    long getSubproblemAverageExecutionTime() {
        return subproblemAverageExecutionTime;
    }

    // Sets the average execution time of the pattern generation subproblem's solution,
    // in microseconds.
    void setSubproblemAverageExecutionTime(long t) {
        subproblemAverageExecutionTime = t;
    }
};


// GLPK-based solver for the cutting-stock problem that uses linear relaxation and
// pattern/column generation techniques.
class CuttingStockLinearRelaxationSolver : public CuttingStockSolver<double>
{
private:

    // Runtime statistics
    CuttingStockLinearRelaxationSolverRuntimeStatistics runtimeStatistics;

    // Precision-driven comparer for floating point numbers.
    FloatingPointComparer floatingPointComparer;

    // Solver for the pattern/column generation subproblem (integer knapsack).
    IntegerKnapsackSolver<double> knapsackSolver;

public:

    CuttingStockLinearRelaxationSolver() :
            floatingPointComparer(CUTTING_STOCK_LINEAR_RELAXATION_DEFAULT_PRECISION),
            knapsackSolver(&floatingPointComparer)
    { }

    // Constructor. Requires a precision for the floating point comparer.
    CuttingStockLinearRelaxationSolver(double precision) :
        floatingPointComparer(precision),
        knapsackSolver(&floatingPointComparer)
    { }

    // Solves a particular cutting-stock instance using linear relaxation and pattern generation.
    CuttingStockSolution<double>* solve(CuttingStockInstance* instance);

    // Gets statistics from the last run of any solve* method.
    CuttingStockLinearRelaxationSolverRuntimeStatistics& getRuntimeStatistics() {
        return runtimeStatistics;
    }
};

#endif

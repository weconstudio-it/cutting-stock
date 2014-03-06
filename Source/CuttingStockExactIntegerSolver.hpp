#ifndef CUTTING_STOCK_EXACT_INTEGER_SOLVER_H
#define CUTTING_STOCK_EXACT_INTEGER_SOLVER_H

#include "CuttingStockSolver.hpp"
#include "CuttingStockMathProgInstance.hpp"
#include "IntegerSolverBacktrackingMode.hpp"



class CuttingStockExactIntegerSolverRuntimeStatistics
{
private:

    long totalExecutionTime;
    long solverExecutionTime;

public:

    CuttingStockExactIntegerSolverRuntimeStatistics()
    {
        totalExecutionTime = 0;
        solverExecutionTime = 0;
    }

    long getTotalExecutionTime() {
        return totalExecutionTime;
    }

    void setTotalExecutionTime(long t) {
        totalExecutionTime = t;
    }

    long getSolverExecutionTime() {
        return solverExecutionTime;
    }

    void setSolverExecutionTime(long t) {
        solverExecutionTime = t;
    }
};


class CuttingStockExactIntegerSolver : public CuttingStockSolver<int>
{
private:

    IntegerSolverBacktrackingMode backtrackingMode;
    CuttingStockExactIntegerSolverRuntimeStatistics runtimeStatistics;

public:

    CuttingStockExactIntegerSolver() {
        this->backtrackingMode = BEST_LOCAL_BOUND;
    }

    CuttingStockExactIntegerSolver(IntegerSolverBacktrackingMode backtrackingMode) {
        this->backtrackingMode = backtrackingMode;
    }

    CuttingStockSolution<int>* solve(CuttingStockInstance* instance) {
        CuttingStockMathProgInstance mathProgInstance((*instance));
        return solve(&mathProgInstance);
    }

    CuttingStockSolution<int>* solve(CuttingStockMathProgInstance* instance);


    IntegerSolverBacktrackingMode getBacktrackingMode() {
        return backtrackingMode;
    }

    void setBacktrackingMode(IntegerSolverBacktrackingMode backtrackingMode) {
        this->backtrackingMode = backtrackingMode;
    }

    CuttingStockExactIntegerSolverRuntimeStatistics& getRuntimeStatistics() {
        return runtimeStatistics;
    }
};


#endif

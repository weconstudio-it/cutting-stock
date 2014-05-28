#ifndef INTEGER_KNAPSACK_SOLVER_H
#define INTEGER_KNAPSACK_SOLVER_H

#include <assert.h>
#include <map>

#include "Knapsack.hpp"
#include "Comparer.hpp"


// Instance for the integer knapsack problem.
template <typename ValueType>
class IntegerKnapsackInstance: public KnapsackInstance<ValueType, int>
{

};


// Solution for a particular instance of the integer knapsack problem.
template <typename ValueType>
class IntegerKnapsackSolution: public KnapsackSolution<ValueType, int>
{

};


// Solver for the integer knapsack problem.
template <typename ValueType>
class IntegerKnapsackSolver
{

private:

    Comparer<ValueType>* valueComparer;

    ValueType dynamicProgrammingSolve(
            int b, int n, const ValueType value[], const int weight[], int x[]);

public:

    IntegerKnapsackSolver(Comparer<ValueType>* valueComparer) {
        assert(valueComparer != 0);
        this->valueComparer = valueComparer;
    }

    // Solves the integer knapsack problem using a dynamic programming algorithm.
    IntegerKnapsackSolution<ValueType>* solve(IntegerKnapsackInstance<ValueType>* instance);
};


////////////////////////////////////////////////////////////////////////////////////////////////////

//
// C++ requires all template methods to be declared in the header.
//

template <typename ValueType>
IntegerKnapsackSolution<ValueType>* IntegerKnapsackSolver<ValueType>::solve(
        IntegerKnapsackInstance<ValueType>* instance)
{
    // The map of items.
    std::map<int, KnapsackItem<ValueType,int>*> items = instance->getItems();

    // b is the capacity of the knapsack
    // n is the number of available items.
    const int b = instance->getCapacity();
    const int n = items.size();

    // The vectors of values and weights for each item i.
    ValueType* value = new ValueType[1+n];
    int* weight = new int[1+n];

    // A map from the vector indexes i ∈ {1..n} used in the dynamic programming algorithm
    // to the item indexes given by the problem instance interface.
    std::map<int, int> itemIndex;

    // Builds the value and weight vectors, and also the map of item indexes.
    int i = 1;
    for (typename std::map<int, KnapsackItem<ValueType, int>*>::iterator it = items.begin();
            it != items.end(); ++it)
    {
        itemIndex.insert(std::pair<int,int>(i, it->first));
        KnapsackItem<ValueType,int>* item = it->second;

        value[i] = item->getValue();
        weight[i] = item->getWeight();

        i++;
    }

    // x is the optimal solution array
    int* x = new int[1+n];


    //
    // SOLVES THE PROBLEM
    //
    ValueType optimalValue = dynamicProgrammingSolve(b, n, value, weight, x);


    // Builds the solution
    IntegerKnapsackSolution<ValueType>* solution = new IntegerKnapsackSolution<ValueType>();

    solution->setOptimalValue(optimalValue);
    for (int i = 1; i <= n; i++)
        solution->addItemAmount(itemIndex[i], x[i]);


    //
    // CLEAN-UP
    //
    delete[] value;
    delete[] weight;
    delete[] x;


    return solution;
}


// Solves the integer knapsack problem by dynamic programming.
// All array indexes are 1-based.
//
//  - b: the capacity of the knapsack
//  - n: the number of available items.
//  - value: array containing the value of item i, for i in {1 .. n}
//  - weight: array containing the weight of item i, for i in {1 .. n}
//  - x: the optimal solution array. x[i] represents the number of items i allocated in the knapsack.
//       for i in {1 .. n}. The array needs to be pre-allocated with n+1 elements.
//
template <typename ValueType>
ValueType IntegerKnapsackSolver<ValueType>::dynamicProgrammingSolve(
        int b, int n, const ValueType value[], const int weight[], int x[])
{
    //
    // This implementation is based on Lecture 10, "Solving Integer Knapsack Problems by DP", by
    // Dr. Yun-Bin Zhao at School of Mathematics, University of Birmingham
    //
    // The Integer Programming lectures can be found online at:
    // http://web.mat.bham.ac.uk/Y.Zhao/Lect-Notes/IP-lectures
    //

    //
    // DEFINITION
    //

    // Let g[r][λ] be the optimal value for the subproblem with capacity
    // λ and number of items r, where:
    //
    //     r ∈ {0..n}
    //     λ ∈ {0..b}
    //
    ValueType** g = new ValueType*[n+1];
    for (int i = 0; i <= n; i++) {
        g[i] = new ValueType[b+1];
    }


    //
    // INITIALIZATION
    //

    // g[r][0] = 0, ∀ r ∈ {0..n}
    for (int r = 0; r <= n; r++)
        g[r][0] = 0;
    // g[0][λ] = 0, ∀ λ ∈ {0..b}
    for (int lambda = 0; lambda <= b; lambda++)
        g[0][lambda] = 0;


    //
    // FORWARD RECURSION
    // -- Computing g, the table of subproblem optimal values.
    //
    //   for r in (1 .. n):
    //
    //   (1)  g[r][λ] = g[r-1][λ], for λ in (0 .. weight[r-1])
    //
    //   (2)  g[r][λ] = max { g[r-1][λ], value[r] + g[r][λ - weight[r]] }, for λ in (weight[r] .. b)
    //

    for (int r = 1; r <= n; r++)
    {
        // (1)
        for (int lambda = 0; lambda < weight[r]; lambda++) {
            g[r][lambda] = g[r-1][lambda];
        }

        // (2)
        for (int lambda = weight[r]; lambda <= b; lambda++) {
            g[r][lambda] =
                valueComparer->max( g[r-1][lambda] , (value[r] + g[r][lambda - weight[r]]) );
        }
    }

    //
    // BACKWARD RECURSION
    // -- Computing x, the optimal solution for the problem with r = n and λ = b
    //

    // Initialization: λ ← b, r ← n, x ← 0.
    int lambda = b;
    int r = n;
    for (int i = 1; i <= n; i++)
        x[i] = 0;

    // While λ,r > 0, repeat
    while (lambda > 0 && r > 0)
    {
        // if g[r][λ] = g[r−1][λ] set r ← (r − 1)
        if (valueComparer->equals(g[r][lambda], g[r-1][lambda])) {
            r = r - 1;
        }
        // else set x[r] ← (x[r] + 1) and λ ← (λ − weight[r])
        else {
            x[r] = x[r] + 1;
            lambda = lambda - weight[r];
        }
    }


    // The optimal value of this knapsack instance we want to solve
    ValueType optimalValue = g[n][b];


    //
    // CLEAN-UP
    //
    for (int i = 0; i <= n; i++)
        delete[] g[i];
    delete[] g;


    return optimalValue;
}

#endif

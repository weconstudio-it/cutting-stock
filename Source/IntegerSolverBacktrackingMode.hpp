#ifndef BRANCH_AND_BOUND_BACKTRACKING_MODE_H
#define BRANCH_AND_BOUND_BACKTRACKING_MODE_H

#include <glpk.h>

// Controls the backtracking mode of the GLPK branch-and-bound / branch-and-cut solver.
typedef enum
{
    DEPTH_SEARCH = GLP_BT_DFS,
    BREADTH_SEARCH = GLP_BT_BFS,
    BEST_LOCAL_BOUND = GLP_BT_BLB,
    BEST_PROJECTION_HEURISTIC = GLP_BT_BPH
} IntegerSolverBacktrackingMode;

#endif

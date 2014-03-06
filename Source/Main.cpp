#include <unistd.h> // for getopt and access

#include <string>
#include <list>
#include <fstream>
#include <ostream>
#include <iostream>
#include <iomanip>
using namespace std;

#include "CuttingStockInstance.hpp"
#include "CuttingStockInstanceBuilder.hpp"
#include "CuttingStockMathProgInstance.hpp"
#include "CuttingStockHeuristicIntegerSolver.hpp"
#include "CuttingStockExactIntegerSolver.hpp"
#include "IntegerSolverBacktrackingMode.hpp"


#define EXACT_STRATEGY 1
#define HEURISTIC_STRATEGY 2


string getBacktrackingModeName(IntegerSolverBacktrackingMode backtracking) {

    string backtrackingName;

    switch (backtracking) {
        case DEPTH_SEARCH:
            backtrackingName = "DEPTH SEARCH";
        break;

        case BEST_LOCAL_BOUND:
            backtrackingName = "BEST LOCAL BOUND";
        break;

        case BREADTH_SEARCH:
            backtrackingName = "BREADTH SEARCH";
        break;

        case BEST_PROJECTION_HEURISTIC:
            backtrackingName = "BEST PROJECTION HEURISTIC";
        break;

    }

    return backtrackingName;
}


// Prints the generated patterns of a cutting stock solution.
template <typename AllocationType>
void printCuttingStockSolutionPatterns(string identation,
    CuttingStockInstance* instance,
    CuttingStockSolution<AllocationType>* solution)
{
    const int m = instance->getRequirementCount();
    const int n = solution->getPatternCount();

    cout << identation;
    cout << "       ";
    for (int i = 1; i <= m; i++) {
        int width = instance->getWidth(i);
            cout << setw(5) << width;
    }
    cout << "           (allocation)" << endl;

    for (int j = 1; j <= n; j++) {
        CuttingStockPattern* pattern = solution->getPattern(j);
        cout << identation << "  ";
        cout << setw(3) << j << ": ";
        cout << "[ ";
            for (int i = 1; i <= m; i++) {
                int width = instance->getWidth(i);
                cout << setw(3) << pattern->getPieces(width);
                cout << "  ";
            }
        cout << " ]    =>   "
             << solution->getAllocation(j) << endl;
    }

    cout << identation;
    cout << "total:   ";
    for (int i = 1; i <= m; i++) {
        cout << setw(3) << solution->getProducedPieces(instance->getWidth(i)) << "  ";
    }
    cout << endl;
}


void printCuttingStockInstance(CuttingStockInstance* instance)
{
    int m = instance->getRequirementCount();

    cout << "  - Cutting requirements (width instances): " << m << endl
         << "  - Width of the master bar (capacity): " << instance->getBarWidth() << endl
         << endl;

    // Print requirements
    cout << "      ";
    cout << "(widths)       (minimum pieces)" << endl;
    for (int i = 1; i <= m; i++) {
        int width = instance->getWidth(i);
        cout << "        "
             << setw(3) << width << "     =>     "
             << setw(3) << instance->getPieces(width)
             << endl;
    }
}


void solveExactCuttingStock(CuttingStockInstance* instance,
    IntegerSolverBacktrackingMode backtracking, bool humanReadableOutput)
{
    // Solver initialization
    CuttingStockExactIntegerSolver exactSolver;
    exactSolver.setBacktrackingMode(backtracking);

    CuttingStockSolution<int>* solution = exactSolver.solve(instance);

    //
    // Prints the solution
    //
    if (humanReadableOutput)
    {
        cout << "Strategy: EXACT INTEGER" << endl
             << "Branch-and-bound backtracking: " << getBacktrackingModeName(backtracking) << endl
             << endl;

        cout << "(0) PROBLEM INSTANCE" << endl
             << endl;
        printCuttingStockInstance(instance);
        cout << endl;

        cout << "(1) EXACT INTEGER SOLUTION (KANTOROVICH)" << endl
             << endl;

        cout << "  - Total allocated bars (objective function): "
             <<      solution->getTotalAllocation() << endl
             << "  - Generated cutting patterns (columns): "
             <<      solution->getPatternCount() << endl
             << endl;

        printCuttingStockSolutionPatterns("      ", instance, solution);
        cout << endl;

        cout << "(2) RUNTIME STATISTICS:" << endl
             << endl
             << "  - Total execution time (microseconds): "
             <<      exactSolver.getRuntimeStatistics().getTotalExecutionTime() << endl
             << "  - Branch and Bound execution time (microseconds): "
             <<      exactSolver.getRuntimeStatistics().getSolverExecutionTime() << endl
             << endl;
    }
    else {
        // Output format:
        // instances | feasible | total bars allocated | number of generated patterns | branch and bound execution time
        cout << instance->getRequirementCount() << "|"
             << true << "|"
             << solution->getTotalAllocation() << "|"
             << solution->getPatternCount() << "|"
             << exactSolver.getRuntimeStatistics().getSolverExecutionTime() << endl;
    }

    delete solution;
    delete instance;
}


void solveHeuristicCuttingStock(CuttingStockInstance* instance,
        IntegerSolverBacktrackingMode backtracking, bool humanReadableOutput)
{
    // Solver initialization
    CuttingStockLinearRelaxationSolver linearRelaxationSolver;
    CuttingStockHeuristicIntegerSolver heuristicSolver;
    heuristicSolver.setBacktrackingMode(backtracking);

    // Solves the linear relaxation
    CuttingStockSolution<double>* linearRelaxationSolution =
        linearRelaxationSolver.solve(instance);

    // Solves the integer heuristic
    CuttingStockSolution<int>* heuristicSolution =
        heuristicSolver.solve(instance, linearRelaxationSolution);

    //
    // Prints the solution
    //
    if (humanReadableOutput)
    {
        cout << "Strategy: HEURISTIC INTEGER" << endl
             << "Branch-and-bound backtracking: " << getBacktrackingModeName(backtracking) << endl
             << endl;

        cout << "(0) PROBLEM INSTANCE" << endl
             << endl;
        printCuttingStockInstance(instance);
        cout << endl;

        cout << "(1) LINEAR RELAXATION SOLUTION" << endl
             << endl;

        cout << "  - Total bar allocation (objective function): "
             << linearRelaxationSolution->getTotalAllocation() << endl
             << "  - Generated cutting patterns (columns): "
             << linearRelaxationSolution->getPatternCount() << endl
             << endl;

        printCuttingStockSolutionPatterns("      ", instance, linearRelaxationSolution);
        cout << endl;

        cout << "(2) INTEGER HEURISTIC SOLUTION" << endl
             << endl;

        cout << "  - Solution is ";
        if (heuristicSolution != 0) {
            cout << "FEASIBLE." << endl;

            cout << "  - Total allocated bars (objective function): "
                 << heuristicSolution->getTotalAllocation() << endl
                 << "  - Investigated cutting patterns (columns): "
                 << heuristicSolution->getPatternCount() << endl
                 << endl;

            printCuttingStockSolutionPatterns("      ", instance, heuristicSolution);
        }
        else {
            cout << "UNFEASIBLE." << endl;
        }
        cout << endl;

        cout << "(3) RUNTIME STATISTICS:" << endl
             << endl
             << "  - Total execution time (microseconds):" << endl
             <<      heuristicSolver.getRuntimeStatistics().getTotalExecutionTime() << endl
             << "  - Linear relaxation execution time (microseconds): "
             <<      linearRelaxationSolver.getRuntimeStatistics().getTotalExecutionTime() << endl
             << "  - Linear relaxation subproblem average execution time (microseconds): "
             <<      linearRelaxationSolver.getRuntimeStatistics().getSubproblemAverageExecutionTime() << endl
             << "  - Integer heuristic execution time (microseconds): "
             <<      heuristicSolver.getRuntimeStatistics().getHeuristicExecutionTime() << endl
             << endl;
    }
    else
    {
        // Output format:
        // instances | feasible | number of allocated bars | number of investigated patterns | heuristic execution time

        // if solution is feasible
        if (heuristicSolution != 0) {

            cout << instance->getRequirementCount() << "|"
                 << true << "|"
                 << heuristicSolution->getTotalAllocation() << "|"
                 << heuristicSolution->getPatternCount() << "|"
                 << heuristicSolver.getRuntimeStatistics().getHeuristicExecutionTime() << endl;
         }
         else {
            cout << instance->getRequirementCount() << "|"
                 << false << "|"
                 << "-" << "|"
                 << "-" << "|"
                 << heuristicSolver.getRuntimeStatistics().getHeuristicExecutionTime() << endl;
         }
    }

    // Clean-up
    delete instance;
    delete linearRelaxationSolution;
    if (heuristicSolution != 0)
        delete heuristicSolution;
}


void showUsage(char* programName)
{
    cout << "Usage:  " << programName << " [-s strategy] [-b backtracking] [-a] [input-file]" << endl
         << "        " << programName << " [-h]" << endl
         << endl;

    cout << "  input-file is the input file name. If not specified, reads standard input." << endl
         << endl;

    cout << "  -h  : shows this help" << endl
         << endl;

    cout << "  -a  : outputs the significant result fields in a parsable, machine-friendly way so this program" << endl
         << "        can be easily invoked and processed by automation scripts." << endl
         << endl;

    cout << "  -s strategy  : solution strategy to use. Strategy can assume the following values (default: heuristic). " << endl
         << endl
         << "                 - heuristic: solves an integer heuristic applied on top of a linear relaxation solution." << endl
         << "                 - exact: solves an exact integer program based on the Kantorovich formulation." << endl
         << endl;

    cout << "  -b backtracking  : branch-and-bound backtracking mode. Backtracking can assume the following values (default: best-local-bound). " << endl
         << endl
         << "                     - best-local-bound: Best Local Bound backtracking mode." << endl
         << "                     - depth-search: Depth First backtracking mode." << endl
         << endl;

    cout << endl;
}


int main(int argc, char *argv[])
{
    char* programName(argv[0]);

    //
    // Parses command line arguments
    //

    bool humanReadableOutput = true;

    // Extern variables used by C function getopt
    extern char* optarg;
    extern int optind, optopt, opterr;
    opterr = 0; // Disable getopt error messages

    bool error = false;
    int c;

    int strategy = HEURISTIC_STRATEGY;
    IntegerSolverBacktrackingMode backtracking = BEST_LOCAL_BOUND;


    while ((c = getopt(argc, argv, "s:b:ah")) != -1)
    {
        string s;

        switch (c)
        {
            case 'a':
                humanReadableOutput = false;
            break;

            case 's':
                s = optarg;
                if (s == "heuristic")
                    strategy = HEURISTIC_STRATEGY;
                else if (s == "exact")
                    strategy = EXACT_STRATEGY;
                else {
                    error = true;
                    cerr << "Error. Unrecognized strategy: " << s << endl;
                }
                break;

            case 'b':
                s = optarg;
                if (s == "depth-search")
                    backtracking = DEPTH_SEARCH;
                else if (s == "best-local-bound")
                    backtracking = BEST_LOCAL_BOUND;
                else {
                    error = true;
                    cerr << "Error. Unrecognized backtracking mode: " << s << endl;
                }
                break;

            // Show help/usage
            case 'h':
                cout << "Solver for the cutting-stock problem." << endl
                     << "Created by Felipe Dornelas <contact@felipedornelas.com>" << endl
                     << endl;
                showUsage(programName);
                return 0;
            break;

            case ':':
                error = true;
                cerr << "Error. Option -" << (char)optopt << " requires an argument" << endl;
            break;

            case '?':
                error = true;
                cerr << "Error. Unrecognized option: -" << (char)optopt << endl;
            break;
        }
    }

    if (error) {
        showUsage(programName);
        return 1;
    }

    //
    // Builds the cutting-stock problem instance
    //

    CuttingStockInstanceBuilder instanceBuilder;
    CuttingStockInstance* instance = 0;

    // Reads the input file, if has been informed
    if (optind < argc) {
        char* inputFileName = argv[optind];

        // Verifies if the file can be read.
        bool canNotRead = (bool) access(inputFileName, R_OK);
        if (canNotRead) {
            cerr << "Can't read file " << inputFileName << endl;
            return 1;
        }

        ifstream inputFile(inputFileName, ifstream::in);
        instance = instanceBuilder.parseStream(inputFile);
    }
    else {
        // Reads from standard in
        instance = instanceBuilder.parseStream(cin);
    }

    //
    // Solves the cutting-stock problem instance
    //
    switch (strategy) {
        case HEURISTIC_STRATEGY:
            solveHeuristicCuttingStock(instance, backtracking, humanReadableOutput);
        break;
        case EXACT_STRATEGY:
            solveExactCuttingStock(instance, backtracking, humanReadableOutput);
        break;
    }

    return 0;
}

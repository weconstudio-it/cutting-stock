Felipe Augusto Dornelas
Operational Research - Cutting Stock
2012.12

Setup
=====

You need to install the GLPK C libraries. On a reasonably recent version of Ubuntu Linux this can be made as follows:

    sudo apt-get install libglpk-dev libglpk0

Make sure you have installed a decent version of the gcc c++ (g++) compiler and the make utility.

Compile
=======

Switch to the Source directory, and run the command make. This will compile the code, and should generate no errors neither warnings.

You can optionally run the unit-test suite to make sure everything is in place:

    make unit-tests

Execution
=========

Once you have compiled, execute the program cutting-stock. The usage is as follows:

    Usage:  ./cutting-stock [-s strategy] [-b backtracking] [-a] [input-file]
            ./cutting-stock [-h]

    input-file is the input file name. If not specified, reads standard input.

    -h  : shows this help

    -a  : outputs the significant result fields in a parsable, machine-friendly
          way so this program can be easily invoked and processed by automation
          scripts.

    -s strategy  : solution strategy to use. Strategy can assume the following
                   values (default: heuristic).

                   - heuristic: solves an integer heuristic applied on top of a
                       linear relaxation solution.
                   - exact: solves an exact integer program based on the
                       Kantorovich formulation.

    -b backtracking  : branch-and-bound backtracking mode. Backtracking can assume
                       the following values (default: best-local-bound).

                       - best-local-bound: Best Local Bound backtracking mode.
                       - depth-search: Depth First backtracking mode.


Optionally you can execute the exact integer solution by invoking the GLPK standalone solver (glpsol) with the MathProg model that is defined inside the MathProg directory.


Execution Examples
==================

In order to solve using the heuristic and best-local-bound:

    ./cutting-stock -s heuristic -b best-local-bound data/instance{i}.dat

where {i} can be from 1 to 24. Ex: data/instance3.dat

To execute the exact solution with depth-first:

    ./cutting-stock -s exact -b depth-search data/instance{i}.dat

To execute the exact solution by invoking the GLPK standalone solver directly:

    glpsol -m MathProg/CuttingStockExactIntegerSolver.mod -d MathProg/test1.dat

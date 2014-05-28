#include "CuttingStockExactIntegerSolver.hpp"


#include <fstream>
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <string>
using namespace std;

#include "Time.hpp"
#include "GlpkUtil.hpp"


#define MATHPROG_MODEL_FILE_NAME "MathProg/CuttingStockExactIntegerSolver.mod"

#define MATHPROG_DATA_TEMPORARY_FILE_NAME "temp.dat"


string writeTemporaryFile(CuttingStockMathProgInstance* instance)
{

    ofstream temp(MATHPROG_DATA_TEMPORARY_FILE_NAME);
    instance->write(temp);
    temp.close();

    return MATHPROG_DATA_TEMPORARY_FILE_NAME;
}


CuttingStockSolution<int>* CuttingStockExactIntegerSolver::solve(
    CuttingStockMathProgInstance* instance)
{
    Timer totalExecutionTimer;
    Timer solverExecutionTimer;

    totalExecutionTimer.start();

    // Writes the instance to a temporary file in the MathProg data format.
    string mathProgDataFileName = writeTemporaryFile(instance);

    glpkInit();
    glp_prob* mip = glp_create_prob();
    glp_tran* tran = glp_mpl_alloc_wksp();
    int statusCode;

    statusCode = glp_mpl_read_model(tran, MATHPROG_MODEL_FILE_NAME, 1);
    if (statusCode != 0)
        throw runtime_error("Error on reading MathProg model.");

    statusCode = glp_mpl_read_data(tran, mathProgDataFileName.c_str());
    if (statusCode != 0)
        throw runtime_error("Error on translating MathProg data.");

    statusCode = glp_mpl_generate(tran, NULL);
    if (statusCode != 0)
        throw runtime_error("Error on generating MathProg model.");


    solverExecutionTimer.start();

    // GLPK MIP solver control parameters
    glp_iocp* mipParameters = new glp_iocp();
    glp_init_iocp(mipParameters);
    // Defines the branch-and-bound/cut backtracking mode
    mipParameters->bt_tech = (int)backtrackingMode;

    // niko
    mipParameters->tm_lim = 5000;

    glp_mpl_build_prob(tran, mip);
    glp_simplex(mip, NULL);

    statusCode = glp_intopt(mip, mipParameters);

    // niko
    statusCode =0;

    if (statusCode != 0) {
        string msg = "GLPK integer optimizer returned ";
        msg += glpkIntegerOptimizerStatusName(statusCode);
        msg += " / MIP status is ";
        msg += glpkMipStatusName(glp_mip_status(mip));
        throw runtime_error(msg);
    }

    statusCode = glp_mpl_postsolve(tran, mip, GLP_MIP);
    if (statusCode != 0)
        throw runtime_error("Error on postsolving MathProg model.");

    solverExecutionTimer.stop();

    CuttingStockSolution<int>* solution =
        new CuttingStockSolution<int>();

    double v = glp_mip_obj_val(mip);
    solution->setTotalAllocation(v);
    assert(solution->getTotalAllocation() == v);

    int columns = glp_get_num_cols(mip);
    int m = instance->getRequirementCount();
    int n = columns / (1+m);
    int k;

    for (int j = 1; j <= n; j++)
        solution->addPattern(new CuttingStockPattern());

    for (int j = 1; j <= n; j++) {
        int x = glp_mip_col_val(mip, j);
        solution->setAllocation(j, x);
    }

    k = n+1;
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            int x = glp_mip_col_val(mip, k);
            solution->getPattern(j)->addCut(instance->getWidth(i), x);
            k++;
        }
    }

    totalExecutionTimer.stop();

    // Statistics
    runtimeStatistics.setTotalExecutionTime(totalExecutionTimer.getMicroseconds());
    runtimeStatistics.setSolverExecutionTime(solverExecutionTimer.getMicroseconds());

    // Clean-up
    glp_delete_prob(mip);
    // TODO: delete temporary file

    return solution;
}

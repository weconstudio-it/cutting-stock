#include "GlpkUtil.hpp"

using namespace std;

void glpkInit()
{
    // Disables GLPK terminal output
    glp_term_out(GLP_OFF);
}

string glpkMipStatusName(int statusCode) {
    string s;
    switch (statusCode) {
        case 0:
            s = "NORMAL";
            break;

        case GLP_OPT:
            s = "GLP_OPT";
            break;
        case GLP_UNDEF:
            s = "GLP_UNDEF";
            break;
        case GLP_FEAS:
            s = "GLP_FEAS";
            break;
        case GLP_NOFEAS:
            s = "GLP_NOFEAS";
            break;

        default:
            s = "UNKNOWN";
    }
    return s;
}

string glpkIntegerOptimizerStatusName(int statusCode) {
    string s;
    switch (statusCode) {
        case 0:
            s = "NORMAL";
            break;

        case GLP_EBOUND:
            s = "GLP_EBOUND";
            break;
        case GLP_EROOT:
            s = "GLP_EROOT";
            break;
        case GLP_ENOPFS:
            s = "GLP_ENOPFS";
            break;
        case GLP_ENODFS:
            s = "GLP_ENODFS";
            break;
        case GLP_EFAIL:
            s = "GLP_EFAIL";
            break;
        case GLP_EMIPGAP:
            s = "GLP_EMIPGAP";
            break;
        case GLP_ETMLIM:
            s = "GLP_ETMLIM";
            break;
        case GLP_ESTOP:
            s = "GLP_ESTOP";
            break;

        default:
            s = "UNKNOWN";
    }
    return s;
}

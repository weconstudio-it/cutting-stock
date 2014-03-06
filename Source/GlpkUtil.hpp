#ifndef GLPK_UTIL_H
#define GLPK_UTIL_H

#include <glpk.h>
#include <string>

// GLPK initialization
void glpkInit();

std::string glpkIntegerOptimizerStatusName(int statusCode);

std::string glpkMipStatusName(int statusCode);

#endif

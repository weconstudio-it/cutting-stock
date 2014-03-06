#include "CuttingStockMathProgInstance.hpp"

#include <iostream>
#include <ostream>
#include <iomanip>
using namespace std;

void CuttingStockMathProgInstance::write(std::ostream& output)
{
    output << "param W := " << getBarWidth() << ";" << endl;
    output << "param M := " << getRequirementCount() << ";" << endl;
    output << endl;

    output << "param w := " << endl;
    for (int i = 1; i <= getRequirementCount(); i++) {
        output << "    " << setw(3) << i << "  "  << setw(3) << getWidth(i) << endl;
    }
    output << ";" << endl
           << endl;

    output << "param b := " << endl;
    for (int i = 1; i <= getRequirementCount(); i++) {
        output << "    " << setw(3) << i << "  " << setw(3) << getPieces(getWidth(i)) << endl;
    }
    output << ";" << endl
           << endl;

    output << "end;" << endl;
}

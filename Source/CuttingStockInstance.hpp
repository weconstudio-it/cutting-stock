#ifndef CUTTING_STOCK_INSTANCE_H
#define CUTTING_STOCK_INSTANCE_H

#include <map>
#include <deque>
#include <exception>


// Exception thrown when an requirement is not found during a lookup operation.
class CuttingStockRequirementNotFoundException: public std::exception {
    virtual const char* what() const throw() {
        return "Requirement not found.";
    }
};


// A particular instance of the cutting-stock problem.
class CuttingStockInstance {

protected:

    std::map<int, int> requirements;
    std::deque<int> widths;

    int barWidth;

public:

    // Add a cutting requirement to the instance. This is a pair
    // (w, p), where w is a width and p is the number of pieces
    // of width w that should be cut.
    void addRequirement(int width, int pieces) {
        requirements.insert(std::pair<int, int>(width, pieces));
        widths.push_back(width);
    }

    // Gets the number of pieces from the requirement with the given width.
    // If the requirement is not defined throws an exception.
    int getPieces(int width) {
        std::map<int, int>::iterator it = requirements.find(width);
        if (it == requirements.end())
            throw CuttingStockRequirementNotFoundException();
        else
            return it->second;
    }

    // Determines if this instance has an requirement of a given width.
    bool hasRequirement(int width) {
        return requirements.count(width) > 0;
    }

    // Gets the width at a given index in the list.
    // The index is 1-based.
    int getWidth(unsigned index) {
        return widths.at(index - 1);
    }

    // Gets the number of requirements defined by this instance.
    int getRequirementCount() {
        return requirements.size();
    }

    // Gets the fixed width of the bars to be cutted.
    int getBarWidth() {
        return barWidth;
    }

    // Sets the fixed with of the bars to be cutted.
    void setBarWidth(int barWidth) {
        this->barWidth = barWidth;
    }
};

#endif

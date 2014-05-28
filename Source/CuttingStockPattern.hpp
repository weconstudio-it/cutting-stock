#ifndef CUTTING_STOCK_PATTERN_H
#define CUTTING_STOCK_PATTERN_H

#include <exception>
#include <list>
#include <map>
#include <string>
#include <sstream>


// Exception thrown when trying to define a cut that is already defined in the cutting pattern.
class CutAlreadyDefinedInPatternException: public std::exception {
    virtual const char* what() const throw() {
        return "The given cut is already defined in this cutting pattern.";
    }
};


// Represents a pattern that defines how to cut pieces of a given width in
// the cutting-stock problem.
class CuttingStockPattern
{
private:

    // This maps defines how many pieces of each width this pattern cuts.
    std::map<int, int> cuts;

    // Stores the widths that were added to the map of cuts.
    std::list<int> widths;

public:

    // Adds to this pattern a cut that will produce the given number of pieces of the given width.
    // If the cut is already defined, throws an exception.
    void addCut(int width, int pieces) {
        if (getPieces(width) > 0)
            throw CutAlreadyDefinedInPatternException();

        if (pieces > 0) {
            cuts[width] = pieces;
            widths.push_back(width);
        }
    }

    // Gets the number of pieces cut with the given width by this pattern.
    // If there are not cuts defined by this pattern producing pieces of the given width, returns 0.
    int getPieces(int width) {
        std::map<int, int>::iterator it = cuts.find(width);
        if (it == cuts.end())
            return 0;
        else
            return it->second;
    }

    // Gets the number of cuts defined by this pattern.
    int getCutsCount() {
        return cuts.size();
    }

    // Gets the list of widths that will be cut by this pattern producing a numer of pieces greater
    // than zero.
    std::list<int> const& getWidths() {
        return widths;
    }

    // Returns a string representation of this cutting pattern.
    std::string toString() {
        std::ostringstream s;
        for (std::list<int>::iterator it = widths.begin(); it != widths.end(); it++) {
            int width = (*it);
            int pieces = getPieces(width);
            s << "(" << width << " => " << pieces << ") ";
        }
        return s.str();
    }

    // Creates a deep copy of this instance.
    CuttingStockPattern* clone() {
        CuttingStockPattern* clone = new CuttingStockPattern();
        for (std::map<int, int>::iterator it = cuts.begin(); it != cuts.end(); it++) {
            int width = it->first;
            int pieces = it->second;
            clone->addCut(width, pieces);
        }
        return clone;
    }
};

#endif

#include <iostream> // Include input/output stream library for cin/cout
#include "Date.h"   // Include the Date class definition
using namespace std; // Use the standard namespace

#ifndef UNAVAILABLEPERIOD_H // Prevent multiple inclusion of this header file
#define UNAVAILABLEPERIOD_H

// Class representing a period when something is unavailable
class UnavailablePeriod {
    Date start, end; // Start and end dates of the unavailable period

public:
    // Constructor with default values (default-constructed Dates)
    UnavailablePeriod(Date s = Date(), Date e = Date());

    // Check if a given period [s, e] overlaps with this unavailable period
    bool isOverlap(Date s, Date e);

    // Print the unavailable period (start and end dates)
    void printPeriod();

    // Overload input operator to read an UnavailablePeriod from input stream
    friend istream& operator>>(istream& in, UnavailablePeriod& period);

    // Overload output operator to write an UnavailablePeriod to output stream
    friend ostream& operator<<(ostream& out, UnavailablePeriod period);
};

#endif // End of include guard
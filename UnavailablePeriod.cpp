#include <iostream> // For input/output operations
#include "UnavailablePeriod.h" // Include the header for UnavailablePeriod class
using namespace std; // Use the standard namespace

// Constructor for UnavailablePeriod, initializes start and end dates
UnavailablePeriod::UnavailablePeriod(Date s, Date e)
    : start(s), end(e) {}

// Method to check if the period [s, e] overlaps with this unavailable period
bool UnavailablePeriod::isOverlap(Date s, Date e) {
    // If the start of this period is after the end of the other, or
    // the start of the other is after the end of this, there is no overlap
    if (start > e || s > end) return false;
    return true; // Otherwise, periods overlap
}

// Method to print the unavailable period in the format: start - end
void UnavailablePeriod::printPeriod(){
    start.showDate(); // Print start date
    cout << " - ";    // Separator
    end.showDate();   // Print end date
    cout << endl;     // Newline
}

// Overload input operator to read start and end dates from input stream
istream& operator>>(istream& in, UnavailablePeriod& period) {
    in >> period.start >> period.end;
    return in;
}

// Overload output operator to write start and end dates to output stream
ostream& operator<<(ostream& out, UnavailablePeriod period) {
    out << period.start << " " << period.end << endl;
    return out;
}
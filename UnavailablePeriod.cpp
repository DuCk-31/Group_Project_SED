#include <iostream>
#include "UnavailablePeriod.h"
using namespace std;

UnavailablePeriod::UnavailablePeriod(Date s, Date e)
    : start(s), end(e) {}

bool UnavailablePeriod::isOverlap(Date s, Date e) {
    if (start > e || s > end) return false;
    return true;
}

istream& operator>>(istream& in, UnavailablePeriod& period) {
    in >> period.start >> period.end;
    return in;
}

ostream& operator<<(ostream& out, UnavailablePeriod period) {
    out << period.start << " " << period.end << endl;
    return out;
}
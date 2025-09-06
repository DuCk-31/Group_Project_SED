#include <iostream>
#include "Date.h"
using namespace std;

#ifndef UNAVAILABLEPERIOD_H
#define UNAVAILABLEPERIOD_H


class UnavailablePeriod {
    Date start, end;

public:
    UnavailablePeriod(Date s = Date(), Date e = Date());

    bool isOverlap(Date s, Date e);

    friend istream& operator>>(istream& in, UnavailablePeriod& period);
    friend ostream& operator<<(ostream& out, UnavailablePeriod period);
};

#endif
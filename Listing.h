#include <iostream>
#include "Date.h"
using namespace std;

#ifndef LISTING_H
#define LISTING_H


class Listing{
    bool status; // 1 is list 0 is unlist
    float dailyPrice;
    int location;
    float ratingRequirement;
    Date startDate, endDate;

    public:

    Listing(bool status = 0, float dailyPrice = -1, int location = -1, float ratingRequirement = -1,
    Date startDate = Date(), Date endDate = Date());

    void listMotorbike();

    void unlistMotorbike();

    void printInfo();

    bool checkStatus();

    bool checkRequirement(float renterRating);

    bool checkAvailable(Date start, Date end);

    bool checkLocation(int location);

    float calculateTotal(int days);
    
    friend ostream& operator << (ostream &out, Listing listing);
    friend istream& operator >> (istream &in, Listing &listing);
};

#endif
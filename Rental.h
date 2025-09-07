#include <iostream>
#include "Date.h"
#include "Motorbike.h"
using namespace std;

#ifndef RENTAL_H
#define RENTAL_H

class Rental{
    Date startDate, endDate;
    string renterName, ownerName;
    float renterRating;
    Motorbike bike;
    bool status; // 0 is rejcted 1 is accepted

    public:

    Rental(Date startDate = Date(), Date endDate = Date(), string renterName = string(),
    string ownerName = string(), Motorbike bike = Motorbike(), bool status = 0, int renterRating = -1);

    Date getDate(int choice);

    Motorbike getBike();

    void changeStatus(bool status);

    void show2Owner();

    void show2Renter();

    void showHistory();

    void printInfo(bool printStatus);

    friend ostream& operator << (ostream& out, Rental rental);
    friend istream& operator >> (istream& in, Rental &rental);


};

#endif
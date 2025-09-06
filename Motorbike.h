#include <iostream>
#include "Date.h"
using namespace std;

#ifndef MOTORBIKE_H
#define MOTORBIKE_H


class Motorbike{
    string brand, model, color, licensePlate, engineSize;
    int yearMade;

    public:

    //constructor
    Motorbike(string brand = "N/A", string model = "N/A", string color = "N/A", 
    string licensePlate = "N/A",string engineSize = "N/A", int yearMade = 0);

    void insertMotorbike();

    bool checkSize();

    bool checkExist();

    string showMotorbike();

    void editMotorbike();

    void show2Renter(Date startDate, Date endDate, string ownerName, bool status);

    friend ostream& operator << (ostream &out, Motorbike bike);
    friend istream& operator >> (istream &in, Motorbike &bike);
};

#endif
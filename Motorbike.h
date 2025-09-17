#include <iostream>
#include "Date.h"
using namespace std;

#ifndef MOTORBIKE_H
#define MOTORBIKE_H

// Motorbike class to represent a motorbike's information
class Motorbike{
    string brand, model, color, licensePlate, engineSize; // Motorbike details
    int yearMade; // Year the motorbike was made

    public:

    //constructor
    Motorbike(string brand = "N/A", string model = "N/A", string color = "N/A", 
    string licensePlate = "N/A",string engineSize = "N/A", int yearMade = 0);

    void insertMotorbike(); // Insert a new motorbike's information

    bool checkSize(); // Check if engine size is greater than 50cc

    bool checkExist(); // Check if the motorbike exists (licensePlate not "N/A")

    string showMotorbike(); // Return a string with brand, model, and engine size

    void editMotorbike(); // Edit motorbike information

    void printInfo(); // Print all motorbike information

    void show2Renter(Date startDate, Date endDate, string ownerName, bool status); // Show info to renter

    // Overload output operator to write Motorbike object to output stream
    friend ostream& operator << (ostream &out, Motorbike bike);
    // Overload input operator to read Motorbike object from input stream
    friend istream& operator >> (istream &in, Motorbike &bike);
};

#endif
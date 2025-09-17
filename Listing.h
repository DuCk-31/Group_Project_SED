#include <iostream>
#include "Date.h"
using namespace std;

#ifndef LISTING_H
#define LISTING_H

// Listing class to represent a motorbike listing for rent
class Listing{
    bool status; // 1 is list 0 is unlist
    float dailyPrice; // Daily rental price in credit points
    int location; // 1 for HCM, 2 for Ha Noi
    float ratingRequirement; // Minimum renter rating required
    Date startDate, endDate; // Available period for the listing

    public:

    // Constructor with default values for all members
    Listing(bool status = 0, float dailyPrice = -1, int location = -1, float ratingRequirement = -1,
    Date startDate = Date(), Date endDate = Date());

    // Method to list a motorbike for rent
    void listMotorbike();

    // Method to unlist a motorbike (reset listing)
    void unlistMotorbike();

    // Method to print all listing information
    void printInfo();

    // Method to check if the listing is active
    bool checkStatus();

    // Method to check if a renter meets the rating requirement
    bool checkRequirement(float renterRating);

    // Method to check if the requested period is available
    bool checkAvailable(Date start, Date end);

    // Method to check if the location matches
    bool checkLocation(int location);

    // Method to calculate the total price for a given number of days
    float calculateTotal(int days);
    
    // Overload output operator to write Listing object to output stream
    friend ostream& operator << (ostream &out, Listing listing);

    // Overload input operator to read Listing object from input stream
    friend istream& operator >> (istream &in, Listing &listing);
};

#endif
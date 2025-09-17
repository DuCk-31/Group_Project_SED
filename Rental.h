#include <iostream> // For input/output operations
#include "Date.h"   // Include the Date class definition
#include "Motorbike.h" // Include the Motorbike class definition
using namespace std; // Use the standard namespace

#ifndef RENTAL_H // Prevent multiple inclusion of this header file
#define RENTAL_H

// Class representing a rental transaction
class Rental{
    Date startDate, endDate; // Rental period start and end dates
    string renterName, ownerName; // Names of renter and owner
    float renterRating; // Rating of the renter
    Motorbike bike; // The motorbike being rented
    bool status; // 0 is rejected, 1 is accepted

    public:

    // Constructor with default values for all members
    Rental(Date startDate = Date(), Date endDate = Date(), string renterName = string(),
    string ownerName = string(), Motorbike bike = Motorbike(), bool status = 0, float renterRating = -1);

    // Get start or end date based on choice (1 for start, 2 for end)
    Date getDate(int choice);

    // Get the Motorbike object
    Motorbike getBike();

    // Change the status of the rental (accepted/rejected)
    void changeStatus(bool status);

    // Show rental info to the owner
    void show2Owner();

    // Show rental info to the renter
    void show2Renter();

    // Show rental history
    void showHistory();

    // Print rental info, optionally print status
    void printInfo(bool printStatus);

    // Overload output operator to write Rental to output stream
    friend ostream& operator << (ostream& out, Rental rental);

    // Overload input operator to read Rental from input stream
    friend istream& operator >> (istream& in, Rental &rental);

};

#endif // End of include guard
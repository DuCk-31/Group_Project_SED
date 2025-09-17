#include <iostream> // For input/output operations
#include <iomanip>  // For output formatting (setw, setfill, setprecision)
#include "Rental.h" // Include the header for Rental class

using namespace std; // Use the standard namespace

// Constructor for Rental class, initializes all member variables
Rental::Rental(Date startDate, Date endDate, string renterName,
    string ownerName, Motorbike bike, bool status, float renterRating)
    : startDate(startDate), endDate(endDate), renterName(renterName),
    ownerName(ownerName), bike(bike), status(status), renterRating(renterRating) {};

// Method to get either the start or end date based on choice (1 for start, otherwise end)
Date Rental::getDate(int choice){
    if (choice == 1) return startDate;
    return endDate;
}

// Method to get the Motorbike object associated with this rental
Motorbike Rental::getBike(){
    return bike;
}

// Method to change the status of the rental (accepted/rejected)
void Rental::changeStatus(bool status){
    this->status = status;
}

// Method to show rental info to the owner (includes dates, rating, and renter name)
void Rental::show2Owner(){
    startDate.showDate(); cout << " - "; endDate.showDate();
    cout << "  |" << setw(15) << setfill(' ') << left << fixed << setprecision(1) << renterRating << right << "|" << renterName << endl;
}

// Method to show rental info to the renter (delegates to Motorbike's show2Renter)
void Rental::show2Renter(){
    bike.show2Renter(startDate, endDate, ownerName, status);    
}

// Method to show rental history (dates, owner, and status)
void Rental::showHistory(){
    startDate.showDate(); cout << " - "; endDate.showDate();
    cout << "  |" << ownerName << "   " 
     << (status == 1?"(Accepted)":"(Rejected)" ) << endl;
}

// Method to print detailed rental information, optionally including status
void Rental::printInfo(bool printStatus){
    cout << "=== Rental Information ===" << endl;
    cout << "Rental Period: "; startDate.showDate(); cout << " - "; endDate.showDate(); cout << endl;
    cout << "Renter Name: " << renterName << endl;
    cout << "Owner Name: " << ownerName << endl;
    cout << "Renter Rating: " << (renterRating == -1 ? "N/A" : to_string(renterRating)) << endl;
    if (printStatus == 1) cout << "Status: " << (status == 1 ? "Accepted" : "Rejected") << endl;
    if (!printStatus) cout << "Status: Pending" << endl;
}

// Overload output operator to write Rental object to output stream
ostream& operator << (ostream& out, Rental rental){
    out << rental.startDate << " " << rental.endDate << endl;
    out << rental.renterName << endl << rental.ownerName << endl;
    out << rental.renterRating << endl;
    out << rental.bike;
    out << rental.status << endl;
    return out;
}

// Overload input operator to read Rental object from input stream
istream& operator >> (istream& in, Rental &rental){
    in >> rental.startDate >> rental.endDate;
    getline(in >> ws, rental.renterName);
    getline(in >> ws, rental.ownerName);
    in >> rental.renterRating >> rental.bike >> rental.status;
    return in;
}
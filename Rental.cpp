#include <iostream>
#include <iomanip>
#include "Rental.h"

using namespace std;

Rental::Rental(Date startDate, Date endDate, string renterName,
    string ownerName, Motorbike bike, bool status, float renterRating)
    : startDate(startDate), endDate(endDate), renterName(renterName),
    ownerName(ownerName), bike(bike), status(status), renterRating(renterRating) {};

Date Rental::getDate(int choice){
    if (choice == 1) return startDate;
    return endDate;
}

Motorbike Rental::getBike(){
    return bike;
}

void Rental::changeStatus(bool status){
    this->status = status;
}

void Rental::show2Owner(){
    startDate.showDate(); cout << " - "; endDate.showDate();
    cout << "  |" << setw(15) << setfill(' ') << left << fixed << setprecision(1) << renterRating << right << "|" << renterName << endl;
}

void Rental::show2Renter(){
    bike.show2Renter(startDate, endDate, ownerName, status);    
}

void Rental::showHistory(){
    startDate.showDate(); cout << " - "; endDate.showDate();
    cout << "  |" << ownerName << "   " 
     << (status == 1?"(Accepted)":"(Rejected)" ) << endl;
}

void Rental::printInfo(bool printStatus){
    cout << "=== Rental Information ===" << endl;
    cout << "Rental Period: "; startDate.showDate(); cout << " - "; endDate.showDate(); cout << endl;
    cout << "Renter Name: " << renterName << endl;
    cout << "Owner Name: " << ownerName << endl;
    cout << "Renter Rating: " << (renterRating == -1 ? "N/A" : to_string(renterRating)) << endl;
    if (printStatus == 1) cout << "Status: " << (status == 1 ? "Accepted" : "Rejected") << endl;
    if (!printStatus) cout << "Status: Pending" << endl;
}

ostream& operator << (ostream& out, Rental rental){
    out << rental.startDate << " " << rental.endDate << endl;
    out << rental.renterName << endl << rental.ownerName << endl;
    out << rental.renterRating << endl;
    out << rental.bike;
    out << rental.status << endl;
    return out;
}

istream& operator >> (istream& in, Rental &rental){
    in >> rental.startDate >> rental.endDate;
    getline(in >> ws, rental.renterName);
    getline(in >> ws, rental.ownerName);
    in >> rental.renterRating >> rental.bike >> rental.status;
    return in;
}
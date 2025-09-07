#include <iostream>
#include "Listing.h"
using namespace std;

Listing::Listing(bool status, float dailyPrice, int location, float ratingRequirement, Date startDate, Date endDate)
:status(status), dailyPrice(dailyPrice), location(location), ratingRequirement(ratingRequirement), startDate(startDate), endDate(endDate){};

void Listing::listMotorbike(){
    string locationString;
    cout << "Motorbike listing" << endl;
    cout << "Enter daily rental rate (in CP): "; cin >> dailyPrice;
    cout << "Enter location: 1. HCM   2.Ha Noi" << endl;
    cout << "Your choice: "; cin >> locationString;
    while(true){
        if (locationString == "1" || locationString == "2") break;
        cout << "Invalid option, please select again: "; cin >> locationString;
    }
    location = stoi(locationString);
    cout << "Enter minimum renter-rating: "; cin >> ratingRequirement;
    while (ratingRequirement > 5 || ratingRequirement < 1){
        cout << "Renter-rating has to be from 1 to 5" << endl;
        cout << "Please enter again: "; cin >> ratingRequirement;
    }
    cout << "Available period: " << endl;
    cout << "Enter start date: "; startDate.insertDate();
    cout << "Enter end date: "; endDate.insertDate();
    while (startDate > endDate){
        cout << "The end date cannot be before the start date!!!" << endl;
        cout << "Please enter the available period again!!! " << endl;
        cout << "Enter start date: "; startDate.insertDate();
        cout << "Enter end date: "; endDate.insertDate();
    }
    status = true;
}

void Listing::unlistMotorbike(){
    *this = Listing();
}

void Listing::printInfo()  {
    cout << "=== Listing Information ===\n";
    cout << "Status             : " << (status ? "Listed" : "Unlisted") << "\n";
    cout << "Daily Price        : ";
    if (dailyPrice >= 0) cout << dailyPrice << "\n";
    else cout << "N/A\n";

    cout << "Location           : ";
    if (location == 1 || location == 2) cout << (location == 1 ? "HCM " : "Ha Noi ") << "\n";
    else cout << "N/A\n";

    cout << "Rating Requirement : ";
    if (ratingRequirement >= 0) cout << ratingRequirement << "\n";
    else cout << "N/A\n";

    cout << "Available Start    : ";
    if (startDate.getDate(3) != 0) startDate.showDate();
    else cout << "N/A";
    cout << "\n";

    cout << "Available End      : ";
    if (endDate.getDate(3) != 0) endDate.showDate();
    else cout << "N/A";
    cout << "\n";
}

bool Listing::checkStatus(){
    return status;
}

bool Listing::checkRequirement(float renterRating){
    return renterRating >= ratingRequirement;
}

bool Listing::checkAvailable(Date start, Date end){
    if (start - startDate >= 0 && endDate - end >= 0) return 1;
    return 0;
}

bool Listing::checkLocation(int location){
    return location == this->location;
}

float Listing::calculateTotal(int days){
    return dailyPrice*days;
}

ostream& operator << (ostream &out, Listing listing){
out << listing.status << " " << listing.dailyPrice << " " 
    << listing.location << " " << listing.ratingRequirement
    << " " << listing.startDate << " " << listing.endDate << endl;
    return out;
}
istream& operator >> (istream &in, Listing &listing){
    in >> listing.status >> listing.dailyPrice >> listing.location;
    in >> listing.ratingRequirement >> listing.startDate >> listing.endDate;
    return in;
}
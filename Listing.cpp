#include <iostream> // For input/output operations
#include "Listing.h" // Include the Listing class definition
using namespace std; // Use the standard namespace

// Function to check if a string is a valid number (digits, at most one dot)
bool isValidNumber(const string& str) {
    bool dotSeen = false;

    if (str.empty()) return false; // Empty string is not valid

    for (size_t i = 0; i < str.size(); i++) {
        if (str[i] == '.') {
            if (dotSeen) return false; // more than one dot
            dotSeen = true;
        } else if (!isdigit(str[i])) {
            return false; // not a digit or dot
        }
    }
    return true;
}

// Constructor for Listing class, initializes all member variables
Listing::Listing(bool status, float dailyPrice, int location, float ratingRequirement, Date startDate, Date endDate)
:status(status), dailyPrice(dailyPrice), location(location), ratingRequirement(ratingRequirement), startDate(startDate), endDate(endDate){};

// Method to list a motorbike for rent
void Listing::listMotorbike(){
    string locationString, dailyPrice, ratingRequirement;
    cout << "Motorbike listing" << endl;
    cout << "Enter daily rental rate (in CP): "; cin >> dailyPrice;
    while (!isValidNumber(dailyPrice)){ //error handling
        cout << "Please enter the daily rental rate again (in CP) again: "; cin >> dailyPrice;
    }
    this->dailyPrice = stof(dailyPrice);
    
    cout << "Enter location: 1. HCM   2.Ha Noi" << endl;
    cout << "Your choice: "; cin >> locationString;
    while(true){ //error handling
        if (locationString == "1" || locationString == "2") break;
        cout << "Invalid option, please select again: "; cin >> locationString;
    }
    location = stoi(locationString);

    cout << "Enter minimum renter-rating (1.0 - 5.0): ";
    cin >> ratingRequirement;
    while (!isValidNumber(ratingRequirement) || stof(ratingRequirement) < 1.0 || stof(ratingRequirement) > 5.0) { //error handling
        cout << "Renter-rating must be between 1.0 and 5.0" << endl;
        cout << "Please enter again: ";
        cin >> ratingRequirement;
    }
    this->ratingRequirement = stof(ratingRequirement);

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

// Method to unlist a motorbike (reset listing)
void Listing::unlistMotorbike(){
    *this = Listing();
}

// Method to print all listing information
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

// Method to check if the listing is active
bool Listing::checkStatus(){
    return status;
}

// Method to check if a renter meets the rating requirement
bool Listing::checkRequirement(float renterRating){
    return renterRating >= ratingRequirement;
}

// Method to check if the requested period is available
bool Listing::checkAvailable(Date start, Date end){
    if (start - startDate >= 0 && endDate - end >= 0) return 1;
    return 0;
}

// Method to check if the location matches
bool Listing::checkLocation(int location){
    return location == this->location;
}

// Method to calculate the total price for a given number of days
float Listing::calculateTotal(int days){
    return dailyPrice*days;
}

// Overload output operator to write Listing object to output stream
ostream& operator << (ostream &out, Listing listing){
out << listing.status << " " << listing.dailyPrice << " " 
    << listing.location << " " << listing.ratingRequirement
    << " " << listing.startDate << " " << listing.endDate << endl;
    return out;
}

// Overload input operator to read Listing object from input stream
istream& operator >> (istream &in, Listing &listing){
    in >> listing.status >> listing.dailyPrice >> listing.location;
    in >> listing.ratingRequirement >> listing.startDate >> listing.endDate;
    return in;
}
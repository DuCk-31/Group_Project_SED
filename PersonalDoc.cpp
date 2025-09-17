#include <iostream>
#include "PersonalDoc.h"
using namespace std;

// Function to check if a passport number is valid
// Format: 1 uppercase letter followed by 7 digits (e.g., B1234567)
bool checkPassportNumber(string passport) {
    if (passport.length() != 8) return 0; // Must be 8 characters
    if (!isalpha(passport[0]) || !isupper(passport[0])) return 0; // First char must be uppercase letter

    for (int i = 1; i < passport.length(); i++) {
        if (!isdigit(passport[i])) return 0; // Remaining must be digits
    }

    return 1; // Valid passport number
}

// Function to check if an ID number is valid (12 digits)
bool checkIDNumber(string idNumber){
    bool checkLength = 1, checkDigit = 1;
    if (idNumber.length() != 12){
        checkLength = 0; // Must be 12 characters
    }

    for (int i = 0; i < idNumber.length(); i++){
        if (idNumber[i] < '0' || idNumber[i] > '9'){
            checkDigit = 0; // All must be digits
        }
    }

    if (checkDigit == 0) cout << "The ID number must contain only digits" << endl;
    if (checkLength == 0) cout << "The ID number must be 12 digits long" << endl;

    if (checkLength == 1 && checkDigit == 1) return 1; // Valid ID
    else return 0; // Invalid ID
}

// Function to check if a license number is valid (12 digits, can't start with 0)
bool checkLicenseNumber(string licenseNumberStr){
    if (licenseNumberStr.length() != 12) return 0; // Must be 12 characters

    if (licenseNumberStr[0] == '0') return 0; // Mustn't start with '0'

    for (int i = 0; i < licenseNumberStr.length(); i++){
        if (!isdigit(licenseNumberStr[i])) {
            cout << "The license number must only contain digits" << endl; // All must be digits
        }
    }
    return 1; // Valid license number
}

// Constructor for PersonalDoc class
PersonalDoc::PersonalDoc(int type, string idNumber, long long licenseNumber, Date expiryDate){
    this->type = type; // Document type (1: Citizen ID, 2: Passport)
    this->idNumber = idNumber; // ID or Passport number
    this->licenseNumber = licenseNumber; // License number
    this->expiryDate = expiryDate; // License expiry date
}

// Method to insert a new personal document
void PersonalDoc::insertDoc(){
    string licenseCheck, typeStr;
    cout << "Choose your personal document type:" << endl;
    cout << "1. Citizen ID" << endl;
    cout << "2. Passport" << endl;
    cout << "Your choice: "; cin >> typeStr;
    while (true){
        if (typeStr == "1" || typeStr == "2" && !typeStr.empty()) break; // Validate input
        cout << "Invalid selection!!! Please select the valid option" << endl;
        cout << "Select again: "; cin >> typeStr;
    }
    type = stoi(typeStr); // Convert to int

    cout << "Enter your ID number: "; cin >> idNumber;

    while (idNumber.empty()){
        cout << "Id number cannot be empty, please enter again: "; cin >> idNumber;
    }

    if (type == 1) {  
        // Citizen ID validation
        while (!checkIDNumber(idNumber)) {
            cout << "Please enter your Citizen ID number again: "; cin >> idNumber;
        }
    } 
    else if (type == 2) {  // Passport
        while (!checkPassportNumber(idNumber)) {
            cout << "Passport must be 1 uppercase letter followed by 7 digits (e.g., B1234567)" << endl;
            cout << "Please enter your Passport number again: "; 
            cin >> idNumber;
        }
    }

    cout << "Do you have a license?" << endl;
    cout << "1. Yes" << endl;
    cout << "2. No" << endl;
    cout << "Your choice: "; cin >> licenseCheck;
    while (true){
        if (licenseCheck == "1" || licenseCheck == "2" && !licenseCheck.empty()) break; // Validate input
        cout << "Invalid selection!!! Please select the valid option" << endl;
        cout << "Select again: "; cin >> licenseCheck;
    }
    
    if (licenseCheck == "1"){
        string licenseNumberStr;
        cout << "Enter your license number: "; cin >> licenseNumberStr;
        while (!checkLicenseNumber(licenseNumberStr)) {
            cout << "The license number has to be 12 digits long and cannot start with 0" << endl;
            cout << "Please enter your license number again: "; cin >> licenseNumberStr;
        }
        licenseNumber = stoll(licenseNumberStr); // Convert to long long
        cout << "Enter expiry date: "; expiryDate.insertDate(); // Insert expiry date
    }
    else {
        licenseNumber = 0; // No license
        expiryDate = Date(); // Empty date
    }
}

// Method to print personal document details
void PersonalDoc::printDoc(){
    cout << (type == 1?"Citizen Card: ":"Passport: ") << idNumber << endl; // Print type and ID
    if (licenseNumber != 0){
        cout << "License number: " << licenseNumber;
        cout << "  Expiry date: "; expiryDate.showDate(); // Print license and expiry
        cout << endl;
    }
    else {
        cout << "License has not been registered!!!" << endl; // No license
    }
}

// Method to check if license is valid at a given date
bool PersonalDoc::checkLicense(Date end){
    if (licenseNumber == 0) return 0; // No license
    if (end > expiryDate) return 0; // License expired
    return 1; // License valid
}

// Method to edit document details
void PersonalDoc::editDoc(int choice){
    if (choice == 4){
        string typeStr;
        cout << "Choose your personal document type:" << endl;
        cout << "1. Citizen ID" << endl;
        cout << "2. Passport" << endl;
        cout << "Your choice: "; cin >> typeStr;
        while (true){
            if (typeStr == "1" || typeStr == "2") break; // Validate input
                cout << "Invalid selection!!! Please select the valid option" << endl;
                cout << "Select again: "; cin >> typeStr; 
        }
        type = stoi(typeStr); // Convert to int

        cout << "Enter your ID number: "; cin >> idNumber;

        if (type == 1) {  
            // Citizen ID validation
            while (!checkIDNumber(idNumber)) {
                cout << "Please enter your Citizen ID number again: "; cin >> idNumber;
            }
        } 
        else if (type == 2) {  // Passport
            while (!checkPassportNumber(idNumber)) {
                cout << "Passport must be 1 uppercase letter followed by 7 digits (e.g., B1234567)" << endl;
                cout << "Please enter your Passport number again: "; 
                cin >> idNumber;
            }
        }
    }
    else if (choice == 5){
        string licenseNumberStr;
        cout << "Enter your new license number: "; cin >> licenseNumberStr;
        while (!checkLicenseNumber(licenseNumberStr)) {
            cout << "The license number has to be as long as 12 digits" << endl;
            cout << "Please enter your license number again: "; cin >> licenseNumberStr;
        }
        licenseNumber = stoll(licenseNumberStr); // Convert to long long
        cout << "Enter license expiry date: "; expiryDate.insertDate(); // Insert new expiry date
    }
}

// Method to delete license information
void PersonalDoc::deleteLicense(){
    this->licenseNumber = 0; // Set license number to 0
    this->expiryDate = Date(); // Reset expiry date
}

// Overloaded output operator for PersonalDoc
ostream& operator << (ostream &out, PersonalDoc Document){
    out << Document.type << " " << Document.idNumber << " " << Document.licenseNumber << endl << Document.expiryDate << endl;
    return out;
}

// Overloaded input operator for PersonalDoc
istream& operator >> (istream &in, PersonalDoc &Document){
    in >> Document.type >> Document.idNumber >> Document.licenseNumber >> Document.expiryDate;
    return in;
}
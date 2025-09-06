#include <iostream>
#include "PersonalDoc.h"
using namespace std;

PersonalDoc::PersonalDoc(int type, string idNumber, long long licenseNumber, Date expiryDate){
    this->type = type;
    this->idNumber = idNumber;
    this->licenseNumber = licenseNumber;
    this->expiryDate = expiryDate;
}

void PersonalDoc::insertDoc(){
    int licenseCheck;
    cout << "Choose your personal document type:   1. Citizen ID   2. Passport" << endl;
    cout << "Your choice: "; cin >> type;
    while(true){
        if (type == 1 || type == 2) break;
        cout << "Invalid selection!!! Please select the valid option" << endl;
        cout << "Select again: "; cin >> type;
    }

    cout << "Enter your ID number: "; cin >> idNumber;
    while (idNumber.length() != 12) {
        cout << "The ID number has to be as long as 12 digits" << endl;
        cout << "Please enter your ID number again: "; cin >> idNumber;
    }

    cout << "Do you have a license?   1. Yes   2. No" << endl;
    cout << "Your choice: "; cin >> licenseCheck;
    while(true){
        if (licenseCheck == 1 || licenseCheck == 2) break;
        cout << "Invalid selection!!! Please select the valid option" << endl;
        cout << "Select again: "; cin >> licenseCheck;
    }
    
    if (licenseCheck == 1){
        cout << "Enter your license number: "; cin >> licenseNumber;
        while(to_string(licenseNumber).length() != 12) {
            cout << "The license number has to be 12 digits long and cannot start with 0" << endl;
            cout << "Please enter your license number again: "; cin >> licenseNumber;
        }
        cout << "Enter expiry date: "; expiryDate.insertDate();
    }
    else if (licenseCheck == 2){
        licenseNumber = 0;
        expiryDate = Date();
    }
}

void PersonalDoc::printDoc(){
    cout << (type == 1 ? "Citizen ID: " : "Passport: ") << idNumber << '\n';
    cout << "License number: " 
              << (licenseNumber == 0 ? "Not registered" : to_string(licenseNumber));
    if (licenseNumber != 0) {
        cout << "  License expiry date: ";
        expiryDate.showDate();
    }
    cout << '\n';
}

bool PersonalDoc::checkLicense(Date end){
    if (licenseNumber == 0) return 0;
    if (end > expiryDate) return 0;
    return 1;
}

void PersonalDoc::editDoc(int choice){
    if (choice == 4){
        cout << "Select your personal document type:   1. Citizen ID   2. Passport" << endl;
        cout << "Your choice: "; cin >> type;
        while(true){
            if (type == 1 || type == 2) break;
            cout << "Invalid selection!!! Please select the valid option" << endl;
            cout << "Select again: "; cin >> type;
        }

        cout << "Enter your new ID number: "; cin >> idNumber;
        while (idNumber.length() != 12){
            cout << "The ID number has to be as long as 12 digits" << endl;
            cout << "Please enter your ID number again: "; cin >> idNumber;
        }
        
    }
    else if (choice == 5){
        cout << "Enter your new license number: "; cin >> licenseNumber;
        while(to_string(licenseNumber).length() != 12) {
            cout << "The license number has to be as long as 12 digits" << endl;
            cout << "Please enter your license number again: "; cin >> licenseNumber;
        }
        cout << "Enter license expiry date: "; expiryDate.insertDate();
    }
}

void PersonalDoc::deleteLicense(){
    this->licenseNumber = 0;
    this->expiryDate = Date();
}

ostream& operator << (ostream &out, PersonalDoc Document){
    out << Document.type << " " << Document.idNumber << " " << Document.licenseNumber << endl << Document.expiryDate << endl;
    return out;
}

istream& operator >> (istream &in, PersonalDoc &Document){
    in >> Document.type >> Document.idNumber >> Document.licenseNumber >> Document.expiryDate;
    return in;
}
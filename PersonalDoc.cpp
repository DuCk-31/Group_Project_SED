#include <iostream>
#include "PersonalDoc.h"
using namespace std;

bool checkPassportNumber(string passport) {
    // Format: 1 uppercase letter followed by 7 digits (e.g., B1234567)
    if (passport.length() != 8) return 0;
    if (!isalpha(passport[0]) || !isupper(passport[0])) return 0;

    for (int i = 1; i < passport.length(); i++) {
        if (!isdigit(passport[i])) return 0;
    }

    return 1;
}

bool checkIDNumber(string idNumber){
    bool checkLength = 1, checkDigit = 1;
    if (idNumber.length() != 12){
        checkLength = 0;
    }

    for (int i = 0; i < idNumber.length(); i++){
        if (idNumber[i] < '0' || idNumber[i] > '9'){
            checkDigit = 0;
        }
    }

    if (checkDigit == 0) cout << "The ID number must contain only digits" << endl;
    if (checkLength == 0) cout << "The ID number must be 12 digits long" << endl;

    if (checkLength == 1 && checkDigit == 1) return 1;
    else return 0;
}

PersonalDoc::PersonalDoc(int type, string idNumber, long long licenseNumber, Date expiryDate){
    this->type = type;
    this->idNumber = idNumber;
    this->licenseNumber = licenseNumber;
    this->expiryDate = expiryDate;
}

void PersonalDoc::insertDoc(){
    string licenseCheck, typeStr;
    cout << "Choose your personal document type:" << endl;
    cout << "1. Citizen ID" << endl;
    cout << "2. Passport" << endl;
    cout << "Your choice: "; cin >> typeStr;
    while (true){
        if (typeStr == "1" || typeStr == "2" && !typeStr.empty()) break;
        cout << "Invalid selection!!! Please select the valid option" << endl;
        cout << "Select again: "; cin >> typeStr;
    }
    type = stoi(typeStr);

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
        if (licenseCheck == "1" || licenseCheck == "2" && !licenseCheck.empty()) break;
        cout << "Invalid selection!!! Please select the valid option" << endl;
        cout << "Select again: "; cin >> licenseCheck;
    }
    
    if (licenseCheck == "1"){
        cout << "Enter your license number: "; cin >> licenseNumber;
        while (to_string(licenseNumber).length() != 12 ) {
            cout << "The license number has to be 12 digits long and cannot start with 0" << endl;
            cout << "Please enter your license number again: "; cin >> licenseNumber;
        }
        cout << "Enter expiry date: "; expiryDate.insertDate();
    }
    else {
        licenseNumber = 0;
        expiryDate = Date();
    }
}

void PersonalDoc::printDoc(){
    cout << (type == 1?"Citizen Card: ":"Passport: ") << idNumber << endl;
    if (licenseNumber != 0){
        cout << "License number: " << licenseNumber;
        cout << "  Expiry date: "; expiryDate.showDate();
        cout << endl;
    }
    else {
        cout << "License has not been registered!!!" << endl;
    }
}

bool PersonalDoc::checkLicense(Date end){
    if (licenseNumber == 0) return 0;
    if (end > expiryDate) return 0;
    return 1;
}

void PersonalDoc::editDoc(int choice){
    if (choice == 4){
        string typeStr;
        cout << "Choose your personal document type:" << endl;
        cout << "1. Citizen ID" << endl;
        cout << "2. Passport" << endl;
        cout << "Your choice: "; cin >> typeStr;
        while (true){
            if (typeStr == "1" || typeStr == "2") break;
                cout << "Invalid selection!!! Please select the valid option" << endl;
                cout << "Select again: "; cin >> typeStr; 
        }
        type = stoi(typeStr);

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
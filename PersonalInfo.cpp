#include <iostream>
#include <regex>
#include "PersonalInfo.h"

using namespace std;


bool checkPhonenum(string phoneNumber){
    regex domesticPattern("^(0[35789][0-9]{8})$");
    regex internationalPattern("^\\+84[35789][0-9]{8}$");
    if (regex_match(phoneNumber, domesticPattern) || regex_match(phoneNumber, internationalPattern)) return 1;
    return 0;
}

PersonalInfo::PersonalInfo(string username, string fullName, string email, string phoneNumber){
    this->username = username;
    this->fullName = fullName;
    this->email = email;
    this->phoneNumber = phoneNumber;
}

string PersonalInfo::getInfo(int choice){
    if (choice == 1) return username;
    if (choice == 2) return fullName;
    if (choice == 3) return email;
    return phoneNumber;
}
    
void PersonalInfo::insertInfo(string username) {
    regex emailPattern("(^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,}$)");
    this->username = username;
    cout << "Enter your full name: "; getline(cin, fullName); 
    while (fullName.empty()){
        cout << "Full name cannot be empty, please enter again: "; getline(cin, fullName);
    }
    cout << "Enter your email: "; cin >> email;
    while (!regex_match(email, emailPattern)){
        cout << "The format for your email is invalidate" << endl;
        cout << "Please enter your email again: "; cin >> email;
    }
    cout << "Enter your phone number (start with 0 or +84): "; cin >> phoneNumber;
    while (!checkPhonenum(phoneNumber)){
        cout << "Wrong phone number format" << endl;
        cout << "The validate Vietnamese phone number has to start with 0 or +84" << endl;
        cout << "After the 0 or +84 has to be 3, 5, 7, 8 or 9" << endl;
        cout << "There has to be 9 digits after 0 or +84" << endl;
        cout << "Please enter your phone number again: "; cin >> phoneNumber;
    }
}

void PersonalInfo::printInfo(){
    cout << "=== Personal Information ===" << endl;
    cout << "Full name: " << fullName << "  ";
    cout << "Username: " << username << endl;
    cout << "Email: " << email << "  ";
    cout << "Phone number: " << phoneNumber << endl;
}

void PersonalInfo::editInfo(int choice){
    if (choice == 1) {
        cout << "Enter your new full name: "; getline(cin, fullName);
        while (fullName.empty()){
            cout << "Full name cannot be empty, please enter again: "; getline(cin, fullName);
        }
        cout << "Your full name has been changed!!!" << endl;
    }
    else if (choice == 2) {
        regex emailPattern("(^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,}$)");
        cout << "Enter your new email: "; cin >> email;
        while (!regex_match(email, emailPattern)){
            cout << "The format for your email is invalidate" << endl;
            cout << "Please enter your email again: "; cin >> email;
        }
        cout << "Your email has been changed!!!" << endl;
    }
    else if (choice == 3){
        cout << "Enter your new phone number (start with 0 or +84): "; cin >> phoneNumber;
        while (!checkPhonenum(phoneNumber)){
            cout << "Wrong phone number format" << endl;
            cout << "The validate Vietnamese phone number has to start with 0 or +84" << endl;
            cout << "After the 0 or +84 has to be 3, 5, 7, 8 or 9" << endl;
            cout << "There has to be 9 digits after 0 or +84" << endl;
            cout << "Please enter your phone number again: "; cin >> phoneNumber;
        }
        cout << "Your phone number has been changed!!!" << endl;
    }
}

ostream& operator << (ostream& out, PersonalInfo PersonalInfo){
    out << PersonalInfo.username << endl;
    out << PersonalInfo.fullName << endl;
    out << PersonalInfo.email << endl;
    out << PersonalInfo.phoneNumber << endl;
    return out;
}

istream& operator >> (istream& in, PersonalInfo &PersonalInfo){
    getline(in >> ws, PersonalInfo.username);
    getline(in >> ws, PersonalInfo.fullName);
    in >> PersonalInfo.email;
    in >> PersonalInfo.phoneNumber;
    return in;
}
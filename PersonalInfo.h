#include <iostream>
using namespace std;

#ifndef PERSONAL_INFO_H
#define PERSONAL_INFO_H

class PersonalInfo{
    string username, email, fullName, phoneNumber;
    public:

    //constructor
    PersonalInfo(string username = string(), string fullName = string(), string email = string(), string phoneNumber = string());

    string getInfo(int choice);
    
    void insertInfo(string username);

    void printInfo();

    void editInfo(int choice);

    friend ostream& operator << (ostream& out, PersonalInfo PersonalInfo);
    friend istream& operator >> (istream& in, PersonalInfo &persinal_info);
};

#endif
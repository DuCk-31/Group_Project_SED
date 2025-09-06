#include <iostream>
#include "Date.h"
using namespace std;

#ifndef PERSONAL_DOC_H
#define PERSONAL_DOC_H


class PersonalDoc{
    int type;
    string idNumber;
    long long licenseNumber;
    Date expiryDate;

    public:

    PersonalDoc(int type = -1, string idNumber = string(), long long licenseNumber = 0, Date expiryDate = Date());

    void insertDoc();

    void printDoc();

    bool checkLicense(Date end);

    void editDoc(int choice);

    void deleteLicense();

    friend ostream& operator << (ostream &out, PersonalDoc Document);
    friend istream& operator >> (istream &in, PersonalDoc &Document);

};

#endif
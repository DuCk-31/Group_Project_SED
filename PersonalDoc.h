#include <iostream>
#include "Date.h"
using namespace std;

#ifndef PERSONAL_DOC_H
#define PERSONAL_DOC_H

// PersonalDoc class to represent a user's personal document (ID, license, etc.)
class PersonalDoc{
    int type;                  // Document type (1: Citizen ID, 2: Passport)
    string idNumber;           // ID or Passport number
    long long licenseNumber;   // License number (if any)
    Date expiryDate;           // Expiry date of the license

    public:

    // Constructor with default values for all members
    PersonalDoc(int type = -1, string idNumber = string(), long long licenseNumber = 0, Date expiryDate = Date());

    void insertDoc();          // Insert a new personal document

    void printDoc();           // Print personal document details

    bool checkLicense(Date end); // Check if license is valid at a given date

    void editDoc(int choice);  // Edit document details

    void deleteLicense();      // Delete license information

    // Overload output operator to write PersonalDoc to output stream
    friend ostream& operator << (ostream &out, PersonalDoc Document);
    // Overload input operator to read PersonalDoc from input stream
    friend istream& operator >> (istream &in, PersonalDoc &Document);

};

#endif
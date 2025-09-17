#include <iostream> // For input/output operations
using namespace std;

#ifndef DATE_H // Prevent multiple inclusion of this header file
#define DATE_H

// Date class to represent a calendar date
class Date {
    int day, month, year; // Private member variables for day, month, year
public:
    // Constructor with default values for day, month, year
    Date(int day = 0, int month = 0, int year = 0);

    // Method to get day, month, or year based on choice (1=day, 2=month, 3=year)
    int getDate(int choice);

    // Method to prompt user to enter a valid date and set the Date object
    void insertDate();

    // Method to display the date in dd/mm/yyyy format
    void showDate();

    // Static-like method to get today's date as a Date object
    Date today();

    // Overload output operator to write Date to output stream
    friend ostream& operator<<(ostream &out, Date d1);

    // Overload input operator to read Date from input stream
    friend istream& operator>>(istream &in, Date &d1);

    // Overload > operator to compare two Date objects
    bool operator>(Date &anotherDate);

    // Overload - operator to calculate the difference in days between two Date objects
    double operator-(Date &date2);
};

#endif
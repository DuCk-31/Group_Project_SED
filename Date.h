#include <iostream>
using namespace std;

#ifndef DATE_H
#define DATE_H


class Date {
    int day, month, year;
public:
    Date(int day = 0, int month = 0, int year = 0);

    int getDate(int choice);
    void insertDate();
    void showDate();

    friend std::ostream& operator<<(std::ostream &out, Date d1);
    friend std::istream& operator>>(std::istream &in, Date &d1);

    bool operator>(Date &anotherDate);
    double operator-(Date &date2);
};

#endif
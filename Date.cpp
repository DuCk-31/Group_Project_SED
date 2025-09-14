#include "Date.h"
#include <iomanip>
#include <cstdio>
#include <ctime>

using namespace std;

bool isValidDate(Date date) {
    int day = date.getDate(1);
    int month = date.getDate(2);
    int year = date.getDate(3);

    if (year < 0 || month < 1 || month > 12 || day < 1)
        return 0;

    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // Check for leap year
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
        daysInMonth[1] = 29;

    return day <= daysInMonth[month - 1];
}

Date::Date(int day, int month, int year)
    : day(day), month(month), year(year) {}

int Date::getDate(int choice) {
    if (choice == 1) return day;
    else if (choice == 2) return month;
    else if (choice == 3) return year;
    return -1;
}

void Date::insertDate() {
    scanf("%d/%d/%d", &day, &month, &year);
    while (!isValidDate(*this)) {
        cout << "Invalid date. Please enter again (dd/mm/yyyy): ";
        scanf("%d/%d/%d", &day, &month, &year);
    }
    
}

void Date::showDate() {
    cout << setw(2) << setfill('0') << right << day << "/"
              << setw(2) << setfill('0') << right << month << "/"
              << year;
}

Date Date::today(){
    time_t t = time(nullptr);
    tm tm = {};
    #if defined(_WIN32)
        localtime_s(&tm, &t);
    #else
        localtime_r(&t, &tm);
    #endif
    return Date(tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
}

ostream& operator<<(ostream &out, Date d1) {
    out << d1.day << " " << d1.month << " " << d1.year;
    return out;
}

istream& operator>>(istream &in, Date &d1) {
    in >> d1.day >> d1.month >> d1.year;
    return in;
}

bool Date::operator>(Date &anotherDate) {
    if (year > anotherDate.getDate(3)) return true;
    else if (year == anotherDate.getDate(3)) {
        if (month > anotherDate.getDate(2)) return true;
        if (month == anotherDate.getDate(2)) return day > anotherDate.getDate(1);
        return false;
    }
    return false;
}

double Date::operator-(Date &date2) {
    tm t_start = {};
    tm t_end = {};

    t_start.tm_year = date2.getDate(3) - 1900;
    t_start.tm_mon = date2.getDate(2) - 1;
    t_start.tm_mday = date2.getDate(1);

    t_end.tm_year = year - 1900;
    t_end.tm_mon = month - 1;
    t_end.tm_mday = day;

    time_t date_Start = mktime(&t_start);
    time_t date_End = mktime(&t_end);

    double seconds = difftime(date_End, date_Start);
    return seconds / (60 * 60 * 24);
}


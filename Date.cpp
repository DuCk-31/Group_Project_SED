#include "Date.h"
#include <iomanip>
#include <cstdio>
#include <ctime>

using namespace std;

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
}

void Date::showDate() {
    std::cout << setw(2) << setfill('0') << right << day << "/"
              << setw(2) << setfill('0') << right << month << "/"
              << year;
}

std::ostream& operator<<(std::ostream &out, Date d1) {
    out << d1.day << " " << d1.month << " " << d1.year;
    return out;
}

std::istream& operator>>(std::istream &in, Date &d1) {
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


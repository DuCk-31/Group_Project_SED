#include "Date.h"
#include <iomanip>
#include <cstdio>
#include <sstream>
#include <ctime>

using namespace std;

bool isValidDate(string date) {
    int day, month, year;
    char slash1, slash2;

    stringstream ss(date);
    ss >> day >> slash1 >> month >> slash2 >> year; //split the date into day month year

    // Check parsing success & slashes
    if (ss.fail() || slash1 != '/' || slash2 != '/') return false;

    // Basic validity
    if (year < 0 || month < 1 || month > 12 || day < 1) return false;

    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // Leap year adjustment
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
        daysInMonth[1] = 29;

    return day <= daysInMonth[month - 1];
}

Date::Date(int day, int month, int year)
    : day(day), month(month), year(year) {}

int Date::getDate(int choice) { //get the day/month/year
    if (choice == 1) return day; 
    else if (choice == 2) return month;
    else if (choice == 3) return year;
    return -1;
}

void Date::insertDate() {
    string dateTemp;    
    cin >> dateTemp;    

    // Keep asking until user enters valid date
    while (!isValidDate(dateTemp)) {
        cout << "Invalid date. Please enter again (dd/mm/yyyy): ";
        cin >> dateTemp;
    }

    // Split by '/'
    stringstream ss(dateTemp);
    string part;

    getline(ss, part, '/');  
    day = stoi(part);

    getline(ss, part, '/');  
    month = stoi(part);

    getline(ss, part, '/');  
    year = stoi(part);
}

void Date::showDate() {
    cout << setw(2) << setfill('0') << right << day << "/"
              << setw(2) << setfill('0') << right << month << "/"
              << year;
}

Date Date::today(){
    time_t t = time(nullptr); //get system time
    tm tm = {};
    #if defined(_WIN32) //for winOS
        localtime_s(&tm, &t);
    #else //for LinuxOs & MacoOS
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


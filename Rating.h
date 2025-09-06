#include <iostream>
using namespace std;

#ifndef RATING_H
#define RATING_H


class Rating{
    int stars;
    string raterName;
    string comment;

    public:

    Rating(int stars = -1, string name = string(), string comment = string());

    void rateObj(string username);

    void showRating();

    int getStars();

    friend ostream& operator << (ostream& out, Rating rating);
    friend istream& operator >> (istream& in, Rating &rating);

};

#endif
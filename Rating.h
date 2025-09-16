#include <iostream>
using namespace std;

#ifndef RATING_H
#define RATING_H


class Rating{
    float stars;
    string raterName;
    string comment;

    public:

    Rating(float stars = -1.0, string name = string(), string comment = string());

    void rateObj(string username);

    void showRating();

    float getStars();

    friend ostream& operator << (ostream& out, Rating rating);
    friend istream& operator >> (istream& in, Rating &rating);

};

#endif
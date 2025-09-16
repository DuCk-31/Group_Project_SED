#include <iostream>
#include "Rating.h"

using namespace std;

Rating::Rating(float stars, string name, string comment)
:stars(stars), raterName(name), comment(comment) {};

void Rating::rateObj(string username){
        cout << "Star(s) (1-5): "; cin >> stars;
        while (true){
            if (stars <= 5.0 && stars >= 1.0) break;
            cout << "Enter the star(s) from 1 to 5" << endl;
            cout << "Enter again: "; cin >> stars;
        }

        cin.ignore();
        cout << "Enter your comment: "; getline(cin, comment);
        raterName = username;  
    }

void Rating::showRating(){
        cout << "Rater: " << raterName << "  star(s): " << stars << endl;
        cout << "Comment: " << comment << endl;
    }

float Rating::getStars(){
    return stars;
}

ostream& operator << (ostream& out, Rating rating){
    out << rating.raterName << endl;
    out << rating.comment << endl;
    out << rating.stars << endl;
    return out;
}

istream& operator >> (istream& in, Rating &rating){
    getline(in >> ws, rating.raterName);
    getline(in >> ws, rating.comment);
    in >> rating.stars;
    return in;
}
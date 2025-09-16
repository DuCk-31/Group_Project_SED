#include <iostream>
#include "Rating.h"

using namespace std;

bool isValidRating(string rating) {
    bool dotSeen = false;
    if (rating.empty()) return false;

    for (size_t i = 0; i < rating.size(); i++) {
        if (rating[i] == '.') {
            if (dotSeen) return false; // more than one dot
            dotSeen = true;
        } else if (!isdigit(rating[i])) {
            return false; // not a digit or dot
        }
    }

    if (stof(rating) > 5.0 || stof(rating) < 1.0) return false;
    return true;
}

Rating::Rating(float stars, string name, string comment)
:stars(stars), raterName(name), comment(comment) {};

void Rating::rateObj(string username){
        string starStr;
        cout << "Star(s) (1-5): "; cin >> starStr;
        while (!isValidRating(starStr)){
            cout << "Enter the star(s) from 1 to 5" << endl;
            cout << "Enter again: "; cin >> starStr;
        }

        stars = stof(starStr);

        cin.ignore();
        cout << "Enter your comment: "; getline(cin, comment);
        while (comment.empty()){
            cout << "Enter your comment again: "; getline(cin, comment);
        }
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